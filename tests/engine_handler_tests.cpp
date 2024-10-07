#include <gtest/gtest.h>
#include "engine_handler.hpp"
#include "engine.hpp"
#include "chessConfig.h"

std::string
Search (chess::engine::Engine &engine)
{
    while (engine.IsStop () == false)
        {
        }
    return "test_search";
}

std::string
Response (std::string request_string)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    engine.SetVersion_Major (1);
    engine.SetVersion_Minor (0);
    engine.SetVersion_Patch (0);
    engine.SetSearch (Search);
    std::ostringstream response;
    std::streambuf *oldCoutBuffer = std::cout.rdbuf (response.rdbuf ());
    std::istringstream request (request_string);
    ;
    std::streambuf *oldCinBuffer = std::cin.rdbuf (request.rdbuf ());
    chess::engine::Handler handler (engine, request, response);
    std::string response_string = response.str ();
    std::cin.rdbuf (oldCinBuffer);
    std::cout.rdbuf (oldCoutBuffer);
    return response_string;
}

TEST (engine_handler_tests, engine_handler_uci)
{
    std::string response_string = Response ("uci\n");
    std::string expected_response = "id name test_engine 1.0.0";
    expected_response += " chess " + std::to_string (chess_VERSION_MAJOR) + "." + std::to_string (chess_VERSION_MINOR) + "." + std::to_string (chess_VERSION_PATCH) + " ";
    expected_response += CONFIGURATION + "\n";
    expected_response += "id author test_author\nuciok\n";
    EXPECT_EQ (response_string, expected_response);
}

TEST (engine_handler_tests, engine_handler_stop)
{
    std::string response_string = Response ("go\nstop\n");
    std::string expected_response = "test_search\n";
    EXPECT_EQ (response_string, expected_response);
}

TEST (engine_handler_tests, engine_handler_quit)
{
    std::string response_string = Response ("quit\n");
    std::string expected_response = "";
    EXPECT_EQ (response_string, expected_response);
}

TEST (engine_handler_tests, engine_handler_isready)
{
    std::string response_string = Response ("uci\nisready\n");
    std::string expected_response = "id name test_engine 1.0.0";
    expected_response += " chess " + std::to_string (chess_VERSION_MAJOR) + "." + std::to_string (chess_VERSION_MINOR) + "." + std::to_string (chess_VERSION_PATCH) + " ";
    expected_response += CONFIGURATION + "\n";
    expected_response += "id author test_author\nuciok\n";
    expected_response += "readyok\n";
    EXPECT_EQ (response_string, expected_response);
}

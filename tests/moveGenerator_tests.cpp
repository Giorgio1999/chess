#include <gtest/gtest.h>
#include "engine.hpp"
#include "engine_handler.hpp"
#include <unordered_map>

std::string
Search_mgt (chess::engine::Engine &engine)
{
    while (engine.IsStop () == false)
        {
        }
    return "test_search";
}

std::string
Response_mgt (std::string request_string)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    engine.SetVersion_Major (1);
    engine.SetVersion_Minor (0);
    engine.SetVersion_Patch (0);
    engine.SetSearch (Search_mgt);
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

std::unordered_map<std::string, std::vector<chess::consts::bitboard> >
getTestSuite ()
{
    std::unordered_map<std::string, std::vector<chess::consts::bitboard> > testsuite;
    testsuite["startpos"] = { 1, 20, 400, 8902, 197281, 4865609, 119060324, 3195901860 };
    return testsuite;
}

TEST (moveGenerator_tests, perft_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::unordered_map<std::string, std::vector<chess::consts::bitboard> > testsuite = getTestSuite ();
    for (std::pair<std::string, std::vector<chess::consts::bitboard> > point : testsuite)
        {
            std::string position = point.first;
            std::vector<chess::consts::bitboard> data = point.second;
            std::cout << position << std::endl;
            for (uint i = 0; i < data.size (); i++)
                {
                    engine.Position (position);
                    chess::consts::bitboard result = engine.Perft (i);
                    std::cout << "Perft " << std::to_string (i) << ": " << std::to_string (result) << "/" << std::to_string (data[i]) << std::endl;
                    EXPECT_EQ (result, data[i]);
                }
            std::cout << std::endl;
        }
}

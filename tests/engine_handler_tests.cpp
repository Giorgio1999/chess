#include <chrono>
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
    expected_response += chess::consts::CONFIGURATION + "\n";
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
    expected_response += chess::consts::CONFIGURATION + "\n";
    expected_response += "id author test_author\nuciok\n";
    expected_response += "readyok\n";
    EXPECT_EQ (response_string, expected_response);
}

TEST (engine_handler_tests, engine_handler_position_startpos)
{
    std::string response_string = Response ("position startpos\nshowboard\n");
    std::string expected_response = "\nrnbqkbnr\npppppppp\n--------\n--------\n--------\n--------\nPPPPPPPP\nRNBQKBNR\nFlags:w-KQkq\n\n";
    EXPECT_EQ (response_string, expected_response);
}

TEST (engine_handler_tests, engine_handler_position_fen)
{
    std::string response_string = Response ("position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPP1/RNBQKBNR b KQkq - 0 1\nshowboard\n");
    std::string expected_response = "\nrnbqkbnr\npppppppp\n--------\n--------\n--------\n--------\nPPPPPPP-\nRNBQKBNR\nFlags:b-KQkq\n\n";
    EXPECT_EQ (response_string, expected_response);
}

TEST (engine_handler_tests, engine_handler_position_fen_wenp)
{
    std::string response_string = Response ("position rnbqkbnr/pppppppp/8/8/7P/8/PPPPPPP1/RNBQKBNR b KQkq h3 0 1\nshowboard\n");
    std::string expected_response = "\nrnbqkbnr\npppppppp\n--------\n--------\n-------P\n-------G\nPPPPPPP-\nRNBQKBNR\nFlags:bh3KQkq\n\n";
    EXPECT_EQ (response_string, expected_response);
}

TEST (engine_handler_tests, engine_handler_position_fen_alt)
{
    std::string response_string = Response ("position fen rnbqkbnr/pppppppp/8/8/7P/8/PPPPPPP1/RNBQKBNR b KQkq h3 0 1\nshowboard\n");
    std::string expected_response = "\nrnbqkbnr\npppppppp\n--------\n--------\n-------P\n-------G\nPPPPPPP-\nRNBQKBNR\nFlags:bh3KQkq\n\n";
    EXPECT_EQ (response_string, expected_response);
}

TEST (engine_handler_tests, engine_handler_position_moves)
{
    std::string response_string = Response ("position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 moves e2e4 e7e5\nshowboard\n");
    std::string expected_response = "\nrnbqkbnr\npppp-ppp\n----g---\n----p---\n----P---\n--------\nPPPP-PPP\nRNBQKBNR\nFlags:we6KQkq\n\n";
    EXPECT_EQ (response_string, expected_response);
}

TEST (engine_handler_tests, engine_handler_position_moves_takes)
{
    std::string request_string = Response ("position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1 moves a1a8 h1h8\nshowboard\n");
    std::string expected_response = "\nRnbqkbnR\npppppppp\n--------\n--------\n--------\n--------\nPPPPPPPP\n-NBQKBN-\nFlags:w-----\n\n";
    EXPECT_EQ (request_string, expected_response);
}

TEST (engine_handler_tests, engine_handler_position_moves_castle)
{
    std::string response_string = Response ("position fen r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1 moves e1g1 e8g8\nshowboard\n");
    std::string expected_response = "\nr----rk-\n--------\n--------\n--------\n--------\n--------\n--------\nR----RK-\nFlags:w-----\n\n";
    EXPECT_EQ (response_string, expected_response);
    response_string = Response ("position fen r3k2r/8/8/8/8/8/8/R3K2R w KQkq - 0 1 moves e1c1 e8c8\nshowboard\n");
    expected_response = "\n--kr---r\n--------\n--------\n--------\n--------\n--------\n--------\n--KR---R\nFlags:w-----\n\n";
    EXPECT_EQ (response_string, expected_response);
}

TEST (engine_handler_tests, engine_handler_position_moves_promotion)
{
    std::string response_string = Response ("position fen 8/P7/8/8/8/8/p7/8 w - - 0 1 moves a7a8q a2a1q\nshowboard\n");
    std::string expected_response = "\nQ-------\n--------\n--------\n--------\n--------\n--------\n--------\nq-------\nFlags:w-----\n\n";
    EXPECT_EQ (response_string, expected_response);
    response_string = Response ("position fen 8/P7/8/8/8/8/p7/8 w - - 0 1 moves a7a8r a2a1r\nshowboard\n");
    expected_response = "\nR-------\n--------\n--------\n--------\n--------\n--------\n--------\nr-------\nFlags:w-----\n\n";
    EXPECT_EQ (response_string, expected_response);
    response_string = Response ("position fen 8/P7/8/8/8/8/p7/8 w - - 0 1 moves a7a8n a2a1n\nshowboard\n");
    expected_response = "\nN-------\n--------\n--------\n--------\n--------\n--------\n--------\nn-------\nFlags:w-----\n\n";
    EXPECT_EQ (response_string, expected_response);
    response_string = Response ("position fen 8/P7/8/8/8/8/p7/8 w - - 0 1 moves a7a8b a2a1b\nshowboard\n");
    expected_response = "\nB-------\n--------\n--------\n--------\n--------\n--------\n--------\nb-------\nFlags:w-----\n\n";
    EXPECT_EQ (response_string, expected_response);
}

TEST (engine_handler_tests, engine_handler_position_moves_promotion_takes)
{
    std::string response_string = Response ("position fen 1q6/P7/8/8/8/8/p7/1q6 w - - 0 1 moves a7b8q a2b1q\nshowboard\n");
    std::string expected_response = "\n-Q------\n--------\n--------\n--------\n--------\n--------\n--------\n-q------\nFlags:w-----\n\n";
    EXPECT_EQ (response_string, expected_response);
    response_string = Response ("position fen 1q6/P7/8/8/8/8/p7/1q6 w - - 0 1 moves a7b8r a2b1r\nshowboard\n");
    expected_response = "\n-R------\n--------\n--------\n--------\n--------\n--------\n--------\n-r------\nFlags:w-----\n\n";
    EXPECT_EQ (response_string, expected_response);
    response_string = Response ("position fen 1q6/P7/8/8/8/8/p7/1q6 w - - 0 1 moves a7b8n a2b1n\nshowboard\n");
    expected_response = "\n-N------\n--------\n--------\n--------\n--------\n--------\n--------\n-n------\nFlags:w-----\n\n";
    EXPECT_EQ (response_string, expected_response);
    response_string = Response ("position fen 1q6/P7/8/8/8/8/p7/1q6 w - - 0 1 moves a7b8b a2b1b\nshowboard\n");
    expected_response = "\n-B------\n--------\n--------\n--------\n--------\n--------\n--------\n-b------\nFlags:w-----\n\n";
    EXPECT_EQ (response_string, expected_response);
}

TEST (engine_handler_tests, engine_handler_position_moves_promotion_takes_castle)
{
    std::string response_string = Response ("position fen r3k3/1P6/8/8/8/8/1p6/R3K3 w -Q-q - 0 1 moves b7a8q b2a1q\nshowboard\n");
    std::string expected_response = "\nQ---k---\n--------\n--------\n--------\n--------\n--------\n--------\nq---K---\nFlags:w-----\n\n";
    EXPECT_EQ (response_string, expected_response);
    response_string = Response ("position fen 4k2r/6P1/8/8/8/8/6p1/4K2R w K-k- - 0 1 moves g7h8q g2h1q\nshowboard\n");
    expected_response = "\n----k--Q\n--------\n--------\n--------\n--------\n--------\n--------\n----K--q\nFlags:w-----\n\n";
    EXPECT_EQ (response_string, expected_response);
}

TEST (engine_handler_tests, engine_handler_position_speed)
{
    auto now = std::chrono::high_resolution_clock::now ();
    int npc = 1000;
    for (int i = 0; i < npc; i++)
        {
            std::string response_string = Response ("position fen rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1\n");
        }
    auto end = std::chrono::high_resolution_clock::now ();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds> (end - now).count ();
    std::cout << (float)npc / duration << " ppms" << std::endl;
    EXPECT_GE (duration, 0);
}

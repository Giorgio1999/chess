#include <gtest/gtest.h>
#include "engine.hpp"
#include "engine_handler.hpp"
#include "moves.hpp"
#include <unordered_map>

std::unordered_map<std::string, std::vector<chess::consts::bitboard> >
getTestSuite ()
{
    std::unordered_map<std::string, std::vector<chess::consts::bitboard> > testsuite;
    testsuite[chess::consts::startpos] = { 1, 20, 400, 8902, 197281, 4865609, 119060324 };
    testsuite[chess::consts::kiwipete] = { 1, 48, 2039, 97862, 4085603, 193690690 };
    testsuite["8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -"] = { 1, 14, 191, 2812, 43238, 674624, 11030083, 178633661 };
    testsuite["r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"] = { 1, 6, 264, 9467, 422333, 15833292, 706045033 };
    testsuite["rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"] = { 1, 44, 1486, 62379, 2103487, 89941194 };
    return testsuite;
}

TEST (moveGenerator_tests_long, perft_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::unordered_map<std::string, std::vector<chess::consts::bitboard> > testsuite = getTestSuite ();
    for (std::pair<std::string, std::vector<chess::consts::bitboard> > point : testsuite)
        {
            std::string position = point.first;
            std::cout << position << std::endl;
            std::vector<chess::consts::bitboard> data = point.second;
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

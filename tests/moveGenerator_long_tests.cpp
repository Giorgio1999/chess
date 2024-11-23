#include <gtest/gtest.h>
#include "engine.hpp"
#include "engine_handler.hpp"
#include "moves.hpp"
#include <unordered_map>

std::unordered_map<std::string, std::vector<chess::consts::bitboard> >
getTestSuite ()
{
    std::unordered_map<std::string, std::vector<chess::consts::bitboard> > testsuite;
    testsuite[chess::consts::startpos] = { 1, 20, 400, 8902, 197281, 4865609, 119060324, 3195901860 };
    return testsuite;
}

TEST (moveGenerator_tests_long, perft_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::unordered_map<std::string, std::vector<chess::consts::bitboard> > testsuite = getTestSuite ();
    for (std::pair<std::string, std::vector<chess::consts::bitboard> > point : testsuite)
        {
            std::string position = point.first;
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

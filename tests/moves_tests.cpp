#include <gtest/gtest.h>
#include "moves.hpp"
#include "Defs.hpp"
#include <string>

TEST (moves_tests, move_test_0)
{
    std::string movestring = "e2e4";
    chess::consts::move move = chess::moves::string2move (movestring);
    // e2: 52,0b00110100
    // e4: 36,0b00100100
    chess::consts::move expectedmove = 0b0011010000100100;
    EXPECT_EQ (move, expectedmove);
    std::string newmovestring = chess::moves::move2string (move);
    std::string expectedmovestring = "e2e4";
    EXPECT_EQ (newmovestring, expectedmovestring);
}

TEST (move_tests, move_test_1)
{
    chess::consts::move move = chess::moves::string2move ("a1a8");
    // a1: 56,0b00111000
    // a8: 00,0b00000000
    chess::consts::move expectedmove = 0b0011100000000000;
    EXPECT_EQ (move, expectedmove);
    std::string newmovestring = chess::moves::move2string (move);
    std::string expectedmovestring = "a1a8";
    EXPECT_EQ (newmovestring, expectedmovestring);
}

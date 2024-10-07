#include <gtest/gtest.h>
#include "bitboard.hpp"

TEST (bitboard_tests, bitboard_test_0)
{
    bitboard b = 0;
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), -1);
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), -1);
}

TEST (bitboard_tests, bitboard_test_1)
{
    bitboard b = 1;
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), 0);
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), -1);
}

TEST (bitboard_tests, bitboard_test_64)
{
    bitboard b = 0x8000000000000000;
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), 63);
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), -1);
}

TEST (bitboard_tests, bitboard_test_multiple)
{
    bitboard b = 0;
    b ^= (bitboard)1 << 26;
    b ^= (bitboard)1 << 27;

    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), 26);
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), 27);
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), -1);
}

#include <gtest/gtest.h>
#include "bitboard.hpp"
#include "Defs.hpp"
#include <chrono>

TEST (bitboard_tests, bitboard_test_0)
{
    chess::consts::bitboard b = 0;
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), -1);
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), -1);
}

TEST (bitboard_tests, bitboard_test_1)
{
    chess::consts::bitboard b = 1;
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), 0);
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), -1);
}

TEST (bitboard_tests, bitboard_test_64)
{
    chess::consts::bitboard b = 0x8000000000000000;
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), 63);
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), -1);
}

TEST (bitboard_tests, bitboard_test_multiple)
{
    chess::consts::bitboard b = 0;
    b ^= (chess::consts::bitboard)1 << 26;
    b ^= (chess::consts::bitboard)1 << 27;

    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), 26);
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), 27);
    EXPECT_EQ (chess::bitboard_helper::pop_lsb (b), -1);
}

TEST (bitboard_tests, bitboard_test_speed)
{
    chess::consts::bitboard board = chess::consts::BITBOARD_MAX;
    auto start = std::chrono::high_resolution_clock::now ();
    while (board != 0)
        {
            int t = chess::bitboard_helper::pop_lsb (board);
        }
    auto end = std::chrono::high_resolution_clock::now ();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count () << "s\n";
    EXPECT_LT (elapsed_seconds.count (), 1e-5);
}

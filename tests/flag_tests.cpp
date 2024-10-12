#include <gtest/gtest.h>
#include "flags.hpp"
#include "Defs.hpp"
#include <chrono>

TEST (flag_tests, flag_test_0)
{
    chess::consts::flag b = 0;
    EXPECT_EQ (chess::flags::pop_lsb (b), -1);
    EXPECT_EQ (chess::flags::pop_lsb (b), -1);
}

TEST (flag_tests, flag_test_1)
{
    chess::consts::flag b = 1;
    EXPECT_EQ (chess::flags::pop_lsb (b), 0);
    EXPECT_EQ (chess::flags::pop_lsb (b), -1);
}

TEST (flag_tests, flag_test_8)
{
    chess::consts::flag b = (chess::consts::flag)0b10000000;
    EXPECT_EQ (chess::flags::pop_lsb (b), 7);
    EXPECT_EQ (chess::flags::pop_lsb (b), -1);
}

TEST (flag_tests, flag_test_multiple)
{
    chess::consts::flag b = 0;
    b ^= (chess::consts::flag)1 << 6;
    b ^= (chess::consts::flag)1 << 4;

    EXPECT_EQ (chess::flags::pop_lsb (b), 4);
    EXPECT_EQ (chess::flags::pop_lsb (b), 6);
    EXPECT_EQ (chess::flags::pop_lsb (b), -1);
}

TEST (flag_tests, flag_test_speed)
{
    chess::consts::flag board = chess::consts::BOARD_FLAG_MAX;
    auto start = std::chrono::high_resolution_clock::now ();
    while (board != 0)
        {
            int t = chess::flags::pop_lsb (board);
        }
    auto end = std::chrono::high_resolution_clock::now ();
    std::chrono::duration<double> elapsed_seconds = end - start;
    std::cout << "Elapsed time: " << elapsed_seconds.count () << "s\n";
    EXPECT_LT (elapsed_seconds.count (), 1e-5);
}

TEST (board_flag_tests, board_flag_test_wtp)
{
    chess::consts::flag b = chess::consts::WTP;
    EXPECT_EQ (chess::flags::is_wtp (b), true);
}

TEST (board_flag_tests, board_flag_test_enp)
{
    chess::consts::flag b = chess::consts::ENP;
    EXPECT_EQ (chess::flags::is_enp (b), true);
}

TEST (board_flag_tests, board_flag_test_K)
{
    chess::consts::flag b = chess::consts::K;
    EXPECT_EQ (chess::flags::is_K (b), true);
}

TEST (board_flag_tests, board_flag_test_k)
{
    chess::consts::flag b = chess::consts::k;
    EXPECT_EQ (chess::flags::is_k (b), true);
}

TEST (board_flag_tests, board_flag_test_Q)
{
    chess::consts::flag b = chess::consts::Q;
    EXPECT_EQ (chess::flags::is_Q (b), true);
}

TEST (board_flag_tests, board_flag_test_q)
{
    chess::consts::flag b = chess::consts::q;
    EXPECT_EQ (chess::flags::is_q (b), true);
}

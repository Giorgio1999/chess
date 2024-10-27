#include <gtest/gtest.h>
#include "board.hpp"
#include "Defs.hpp"

TEST (board_tests, board_test_1)
{
    chess::board::Board b;
    std::cout << b.ShowBoard () << std::endl;
    std::string expected = "--------\n--------\n--------\n--------\n--------\n--------\n--------\n--------\nFlags:b-----\n";
    EXPECT_EQ (b.ShowBoard (), expected);
}

TEST (board_tests, board_test_2)
{
    chess::board::Board b;
    b.flip_white_to_play ();
    std::string expected = "--------\n--------\n--------\n--------\n--------\n--------\n--------\n--------\nFlags:w-----\n";
    EXPECT_EQ (b.ShowBoard (), expected);
}

TEST (board_tests, board_test_3)
{
    chess::board::Board b;
    b.flip_castling (chess::consts::castling_rights_name::CASTLE_K);
    std::string expected = "--------\n--------\n--------\n--------\n--------\n--------\n--------\n--------\nFlags:b-K---\n";
    EXPECT_EQ (b.ShowBoard (), expected);
}

TEST (board_tests, board_test_4)
{
    chess::board::Board b;
    b.flip_castling (chess::consts::castling_rights_name::CASTLE_Q);
    std::string expected = "--------\n--------\n--------\n--------\n--------\n--------\n--------\n--------\nFlags:b--Q--\n";
    EXPECT_EQ (b.ShowBoard (), expected);
}

TEST (board_tests, board_test_5)
{
    chess::board::Board b;
    b.flip_castling (chess::consts::castling_rights_name::CASTLE_k);
    std::string expected = "--------\n--------\n--------\n--------\n--------\n--------\n--------\n--------\nFlags:b---k-\n";
    EXPECT_EQ (b.ShowBoard (), expected);
}

TEST (board_tests, board_test_6)
{
    chess::board::Board b;
    b.flip_castling (chess::consts::castling_rights_name::CASTLE_q);
    std::string expected = "--------\n--------\n--------\n--------\n--------\n--------\n--------\n--------\nFlags:b----q\n";
    EXPECT_EQ (b.ShowBoard (), expected);
}

TEST (board_tests, board_test_7)
{
    chess::board::Board b;
    b.set_enpassantable ();
    b.flip_ghost_board (63);
    std::string expected = "--------\n--------\n--------\n--------\n--------\n--------\n--------\n-------G\nFlags:bh1----\n";
    EXPECT_EQ (b.ShowBoard (), expected);
}

TEST (board_tests, board_string2square_H8) { EXPECT_EQ (chess::board::string2square ("h8"), 7); }

TEST (board_tests, board_string2square_A8) { EXPECT_EQ (chess::board::string2square ("a8"), 0); }

TEST (board_tests, board_string2square_H1) { EXPECT_EQ (chess::board::string2square ("h1"), 63); }

TEST (board_tests, board_string2square_A1) { EXPECT_EQ (chess::board::string2square ("a1"), 56); }

TEST (board_tests, board_square2string_H8) { EXPECT_EQ (chess::board::square2string (7), "h8"); }

TEST (board_tests, board_square2string_A8) { EXPECT_EQ (chess::board::square2string (0), "a8"); }

TEST (board_tests, board_square2string_H1) { EXPECT_EQ (chess::board::square2string (63), "h1"); }

TEST (board_tests, board_square2string_A1) { EXPECT_EQ (chess::board::square2string (56), "a1"); }

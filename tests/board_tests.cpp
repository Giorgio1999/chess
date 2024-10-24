#include <gtest/gtest.h>
#include "board.hpp"
#include "Defs.hpp"

TEST (board_tests, board_test_1)
{
    chess::board::Board b;
    std::cout << b.ShowBoard () << std::endl;
    std::string expected = "--------\n--------\n--------\n--------\n--------\n--------\n--------\n--------\nFlags:w-KQkq\n";
    EXPECT_EQ (b.ShowBoard (), expected);
}

TEST (board_tests, board_test_2)
{
    chess::board::Board b;
    b.flip_white_to_play ();
    std::string expected = "--------\n--------\n--------\n--------\n--------\n--------\n--------\n--------\nFlags:b-KQkq\n";
    EXPECT_EQ (b.ShowBoard (), expected);
}

TEST (board_tests, board_test_3)
{
    chess::board::Board b;
    b.flip_castling (chess::consts::castling_rights_name::CASTLE_K);
    std::string expected = "--------\n--------\n--------\n--------\n--------\n--------\n--------\n--------\nFlags:w--Qkq\n";
    EXPECT_EQ (b.ShowBoard (), expected);
}

TEST (board_tests, board_test_4)
{
    chess::board::Board b;
    b.flip_castling (chess::consts::castling_rights_name::CASTLE_Q);
    std::string expected = "--------\n--------\n--------\n--------\n--------\n--------\n--------\n--------\nFlags:w-K-kq\n";
    EXPECT_EQ (b.ShowBoard (), expected);
}

TEST (board_tests, board_test_5)
{
    chess::board::Board b;
    b.flip_castling (chess::consts::castling_rights_name::CASTLE_k);
    std::string expected = "--------\n--------\n--------\n--------\n--------\n--------\n--------\n--------\nFlags:w-KQ-q\n";
    EXPECT_EQ (b.ShowBoard (), expected);
}

TEST (board_tests, board_test_6)
{
    chess::board::Board b;
    b.flip_castling (chess::consts::castling_rights_name::CASTLE_q);
    std::string expected = "--------\n--------\n--------\n--------\n--------\n--------\n--------\n--------\nFlags:w-KQk-\n";
    EXPECT_EQ (b.ShowBoard (), expected);
}

TEST (board_tests, board_test_7)
{
    chess::board::Board b;
    b.flip_enpassantable ();
    b.flip_ghost_board (63);
    std::string expected = "--------\n--------\n--------\n--------\n--------\n--------\n--------\n-------g\nFlags:wH8KQkq\n";
    EXPECT_EQ (b.ShowBoard (), expected);
}

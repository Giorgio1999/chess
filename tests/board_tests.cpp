#include <gtest/gtest.h>
#include <chrono>
#include "board.hpp"
#include "Defs.hpp"
#include "moves.hpp"
#include "fen.hpp"

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

TEST (board_tests, board_makemove_speed)
{
    chess::board::Board b;
    chess::consts::move m = chess::moves::string2move ("e8g1");
    auto now = std::chrono::high_resolution_clock::now ();
    int nmm = 1e5;
    for (int i = 0; i < nmm; i++)
        {
            b.makeMove (123);
        }
    auto end = std::chrono::high_resolution_clock::now ();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (end - now).count ();
    std::cout << (float)nmm / duration << " mpms" << std::endl;
    EXPECT_GE (duration, 0);
}

TEST (board_tests, board_colorboards_test)
{
    std::vector<std::string> stringmoves = { "e2e3", "e7e6", "d2d4", "d7d5", "g1f3", "g8f6", "c1d2", "c8d7", "h1g1", "h8g8", "d1e2", "d8e8", "e1d1", "e8d8", "h2h8q", "h7h1r" };
    chess::board::Board b;
    chess::fen::parse (chess::consts::startpos, b);
    for (int i = 0; i < stringmoves.size (); i++)
        {
            chess::consts::move move = chess::moves::string2move (stringmoves[i]);
            std::cout << chess::moves::move2string (move) << std::endl;
            b.makeMove (move);
            std::array<chess::consts::bitboard, 2> control_color_boards = { 0, 0 };
            std::array<chess::consts::bitboard, 12> piece_boards = b.get_piece_boards ();
            for (int j = 0; j < 6; j++)
                {
                    control_color_boards[0] |= piece_boards[j];
                    control_color_boards[1] |= piece_boards[j + 6];
                }
            EXPECT_EQ (control_color_boards, b.get_color_boards ());
        }
}

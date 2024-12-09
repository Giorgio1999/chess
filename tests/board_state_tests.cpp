#include <gtest/gtest.h>
#include "chess.hpp"

TEST (board_state_tests, repetition_board_state_test)
{
    chess::engine::Engine engine ("Test engine", "Test author");
    // first ocurrence of startpos
    engine.Position (chess::consts::startpos);

    // changing to new pos
    engine.MakeMove (chess::moves::string2move ("b1c3"));
    EXPECT_EQ (engine.IsRepetition (), false);
    engine.MakeMove (chess::moves::string2move ("b8c6"));
    EXPECT_EQ (engine.IsRepetition (), false);

    // second ocurrence of startpos
    engine.MakeMove (chess::moves::string2move ("c3b1"));
    EXPECT_EQ (engine.IsRepetition (), false);
    engine.MakeMove (chess::moves::string2move ("c6b8"));
    EXPECT_EQ (engine.IsRepetition (), false);

    // changing to new pos
    engine.MakeMove (chess::moves::string2move ("b1c3"));
    EXPECT_EQ (engine.IsRepetition (), false);
    engine.MakeMove (chess::moves::string2move ("b8c6"));
    EXPECT_EQ (engine.IsRepetition (), false);

    // third ocurrence of startpos
    engine.MakeMove (chess::moves::string2move ("c3b1"));
    EXPECT_EQ (engine.IsRepetition (), false);
    engine.MakeMove (chess::moves::string2move ("c6b8"));
    EXPECT_EQ (engine.IsRepetition (), true);
}

TEST (board_state_tests, repetition_pawn_board_state_test)
{
    chess::engine::Engine engine ("Test engine", "Test author");
    // first ocurrence of startpos
    engine.Position (chess::consts::startpos);

    // changing to new pos
    engine.MakeMove (chess::moves::string2move ("b1c3"));
    EXPECT_EQ (engine.IsRepetition (), false);
    engine.MakeMove (chess::moves::string2move ("b8c6"));
    EXPECT_EQ (engine.IsRepetition (), false);

    // second ocurrence of startpos
    engine.MakeMove (chess::moves::string2move ("c3b1"));
    EXPECT_EQ (engine.IsRepetition (), false);
    engine.MakeMove (chess::moves::string2move ("c6b8"));
    EXPECT_EQ (engine.IsRepetition (), false);

    // changing to new pos
    engine.MakeMove (chess::moves::string2move ("b1c3"));
    EXPECT_EQ (engine.IsRepetition (), false);
    engine.MakeMove (chess::moves::string2move ("b8c6"));
    EXPECT_EQ (engine.IsRepetition (), false);

    // inserting pawn moves
    engine.MakeMove (chess::moves::string2move ("e2e3"));
    EXPECT_EQ (engine.IsRepetition (), false);
    engine.MakeMove (chess::moves::string2move ("e7e6"));
    EXPECT_EQ (engine.IsRepetition (), false);

    // third ocurrence of startpos
    engine.MakeMove (chess::moves::string2move ("c3b1"));
    EXPECT_EQ (engine.IsRepetition (), false);
    engine.MakeMove (chess::moves::string2move ("c6b8"));
    EXPECT_EQ (engine.IsRepetition (), false);
}

TEST (board_state_tests, stalemate_board_state_test)
{
    chess::engine::Engine engine ("Test engine", "Test author");
    engine.Position ("8/8/8/8/8/1q6/8/K7 w - - 0 1");
    std::cout << engine.ShowBoard () << std::endl;
    EXPECT_EQ (engine.IsStalemate (), true);
    engine.Position ("8/8/8/8/8/1Q6/8/k7 b - - 0 1");
    std::cout << engine.ShowBoard () << std::endl;
    EXPECT_EQ (engine.IsStalemate (), true);
}

TEST (board_state_tests, mate_board_state_test)
{
    chess::engine::Engine engine ("Test engine", "Test author");
    engine.Position ("8/8/8/8/8/8/8/Kqk w - - 0 1");
    std::cout << engine.ShowBoard () << std::endl;
    EXPECT_EQ (engine.IsMate (), true);
    engine.Position ("8/8/8/8/8/8/8/kQK b - - 0 1");
    std::cout << engine.ShowBoard () << std::endl;
    EXPECT_EQ (engine.IsMate (), true);
}

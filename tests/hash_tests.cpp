#include <gtest/gtest.h>
#include "chess.hpp"
#include <unordered_map>

std::unordered_map<std::string, std::vector<chess::consts::bitboard> >
getTestSuite_hash ()
{
    std::unordered_map<std::string, std::vector<chess::consts::bitboard> > testsuite;
    testsuite[chess::consts::startpos] = { 4865609 };
    testsuite[chess::consts::kiwipete] = { 4085603 };
    testsuite["8/2p5/3p4/KP5r/1R3p1k/8/4P1P1/8 w - -"] = { 11030083 };
    testsuite["r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1"] = { 15833292 };
    testsuite["rnbq1k1r/pp1Pbppp/2p5/8/2B5/8/PPP1NnPP/RNBQK2R w KQ - 1 8"] = { 2103487 };
    testsuite["r4rk1/1pp1qppp/p1np1n2/2b1p1B1/2B1P1b1/P1NP1N2/1PP1QPPP/R4RK1 w - - 0 10"] = { 3894594 };
    return testsuite;
}

TEST (hash_tests, hash_test_full)
{
    chess::engine::Engine engine ("test engine", "test author");
    auto testsuite = getTestSuite_hash ();
    for (auto point : testsuite)
        {
            engine.NewGame ();
            engine.Position (point.first);
            auto legalMoves = engine.GetLegalMoves ();
            std::cout << point.first << std::endl;
            for (auto move : legalMoves)
                {
                    std::cout << chess::moves::move2string (move) << std::endl;
                    engine.MakeMove (move);
                    auto board = engine.GetBoard ();
                    EXPECT_EQ (engine.GetCurrentHash (), chess::hash::get_hash (board));
                    engine.UndoMove ();
                }
            std::cout << std::endl;
        }
}

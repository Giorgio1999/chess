#include <gtest/gtest.h>
#include "engine.hpp"
#include "engine_handler.hpp"
#include "moves.hpp"
#include <unordered_map>

TEST (moveGenerator_tests, pawn_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::string allpawnmoves_fen = "p1p5/PP3p2/p1p5/PP6/pp6/P1P5/pp3P2/P1P5 w - - 0 1";
    chess::consts::bitboard perftresults = 11 + 12;
    engine.Position (allpawnmoves_fen);
    std::cout << allpawnmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    chess::consts::bitboard res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
    engine.Position (allpawnmoves_fen);
    engine.MakeMove (chess::moves::string2move ("f2f4"));
    std::cout << allpawnmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
}

TEST (moveGenerator_tests, pawn_enpassant_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::string allpawnmoves_fen = "8/p7/8/1P6/8/8/8/8 b - - 0 1";
    chess::consts::bitboard perftresults = 2;
    engine.Position (allpawnmoves_fen);
    engine.MakeMove (chess::moves::string2move ("a7a5"));
    std::cout << allpawnmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    chess::consts::bitboard res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
    allpawnmoves_fen = "8/8/8/8/1p6/8/P7/8 w - - 0 1";
    engine.Position (allpawnmoves_fen);
    engine.MakeMove (chess::moves::string2move ("a2a4"));
    std::cout << allpawnmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
}

TEST (moveGenerator_tests, knight_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::string knightmoves_fen = "N2N3N/8/1P6/8/N2N3N/1p6/8/N2N3N w - - 0 1";
    chess::consts::bitboard perftresults = 31;
    engine.Position (knightmoves_fen);
    std::cout << knightmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    chess::consts::bitboard res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
    knightmoves_fen = "n2n3n/8/1P6/8/n2n3n/1p6/8/n2n3n b - - 0 1";
    engine.Position (knightmoves_fen);
    std::cout << knightmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
}

TEST (moveGenerator_tests, king_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::string kingmoves_fen = "K6K/8/2P5/3K4/4p3/8/8/K6K w - - 0 1";
    chess::consts::bitboard perftresults = 4 * 3 + 8 - 1 + 1;
    engine.Position (kingmoves_fen);
    std::cout << kingmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    chess::consts::bitboard res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
    kingmoves_fen = "k6k/8/2P5/3k4/4p3/8/8/k6k b - - 0 1";
    engine.Position (kingmoves_fen);
    res = engine.Perft (1);
    std::cout << kingmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    EXPECT_EQ (perftresults, res);
}

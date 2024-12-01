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

TEST (moveGenerator_tests, bishop_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::string bishopmoves_fen = "6pp/8/2P5/3B4/3B4/2P2p2/5p2/8 w - - 0 1";
    chess::consts::bitboard perftresults = 19;
    engine.Position (bishopmoves_fen);
    std::cout << bishopmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    chess::consts::bitboard res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
    bishopmoves_fen = "6PP/8/2p5/3b4/3b4/2p2P2/5P2/8 b - - 0 1";
    engine.Position (bishopmoves_fen);
    std::cout << bishopmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
}

TEST (moveGenerator_tests, rook_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::string rookmoves_fen = "8/8/3P4/3P4/3R3p/8/3P4/8 w - - 0 1";
    chess::consts::bitboard perftresults = 10;
    engine.Position (rookmoves_fen);
    std::cout << rookmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    chess::consts::bitboard res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
    rookmoves_fen = "8/3p4/8/3r3P/3p4/3p4/8/8 b - - 0 1";
    engine.Position (rookmoves_fen);
    std::cout << rookmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
}

TEST (moveGenerator_tests, queen_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::string queenmoves_fen = "3p4/8/2P5/1P1Qp3/2P5/8/8/8 w - - 0 1";
    chess::consts::bitboard perftresults = 19;
    engine.Position (queenmoves_fen);
    std::cout << queenmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    chess::consts::bitboard res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
    queenmoves_fen = "3P4/8/2p5/1p1qP3/2p5/8/8/8 b - - 0 1";
    engine.Position (queenmoves_fen);
    std::cout << queenmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
}
/**/
/*TEST (moveGenerator_tests, king_test)*/
/*{*/
/*    chess::engine::Engine engine ("test_engine", "test_author");*/
/*    std::string kingmoves_fen = "K6K/8/2P5/3K4/4p3/8/8/K6K w - - 0 1";*/
/*    chess::consts::bitboard perftresults = 4 * 3 + 8 - 1 + 1;*/
/*    engine.Position (kingmoves_fen);*/
/*    std::cout << kingmoves_fen << std::endl << engine.LegalMoves () << std::endl;*/
/*    chess::consts::bitboard res = engine.Perft (1);*/
/*    EXPECT_EQ (perftresults, res);*/
/*    kingmoves_fen = "k6k/8/2P5/3k4/4p3/8/8/k6k b - - 0 1";*/
/*    engine.Position (kingmoves_fen);*/
/*    res = engine.Perft (1);*/
/*    std::cout << kingmoves_fen << std::endl << engine.LegalMoves () << std::endl;*/
/*    EXPECT_EQ (perftresults, res);*/
/*}*/

TEST (moveGenerator_tests, king_check_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::string kingmoves_fen = "4r3/8/2p5/8/3K4/8/b4n2/8 w - - 0 1";
    chess::consts::bitboard perftresults = 2;
    engine.Position (kingmoves_fen);
    std::cout << kingmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    chess::consts::bitboard res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
    kingmoves_fen = "8/B4N2/8/3k4/8/2P5/8/4R3 b - - 0 1";
    engine.Position (kingmoves_fen);
    std::cout << kingmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
}

TEST (moveGenerator_tests, king_castle_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::string kingmoves_fen = "8/8/8/8/8/8/P2PPP1P/R3K2R w KQ - 0 1";
    chess::consts::bitboard perftresults = 19;
    engine.Position (kingmoves_fen);
    std::cout << kingmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    chess::consts::bitboard res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);

    kingmoves_fen = "r3k2r/p2ppp1p/8/8/8/8/8/8 b kq - 0 1";
    engine.Position (kingmoves_fen);
    std::cout << kingmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);

    kingmoves_fen = "2r3r1/8/8/8/8/8/P2PPP1P/R3K2R w KQ - 0 1";
    perftresults = 17;
    engine.Position (kingmoves_fen);
    std::cout << kingmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);

    kingmoves_fen = "r3k2r/p2ppp1p/8/8/8/8/8/2R3R1 b kq - 0 1";
    engine.Position (kingmoves_fen);
    std::cout << kingmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);

    kingmoves_fen = "8/8/8/8/8/8/P2PPP1P/R2PKP1R w KQ - 0 1";
    perftresults = 13;
    engine.Position (kingmoves_fen);
    std::cout << kingmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);

    kingmoves_fen = "r2pkp1r/p2ppp1p/8/8/8/8/8/8 b kq - 0 1";
    engine.Position (kingmoves_fen);
    std::cout << kingmoves_fen << std::endl << engine.LegalMoves () << std::endl;
    res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
}

TEST (moveGenerator_tests, wrong_pos_1_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::string fen = chess::consts::startpos;
    engine.Position (fen);
    engine.MakeMove (chess::moves::string2move ("d2d3"));
    engine.MakeMove (chess::moves::string2move ("h7h6"));
    engine.MakeMove (chess::moves::string2move ("c1h6"));
    chess::consts::bitboard perftresults = 21;
    std::cout << fen << std::endl << engine.LegalMoves () << std::endl;
    chess::consts::bitboard res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
}

TEST (moveGenerator_tests, wrong_pos_2_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::string fen = chess::consts::startpos;
    engine.Position (fen);
    engine.MakeMove (chess::moves::string2move ("d2d3"));
    engine.MakeMove (chess::moves::string2move ("c7c6"));
    engine.MakeMove (chess::moves::string2move ("e2e3"));
    engine.MakeMove (chess::moves::string2move ("d8a5"));
    chess::consts::bitboard perftresults = 7;
    std::cout << fen << std::endl << engine.LegalMoves () << std::endl;
    chess::consts::bitboard res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
}

TEST (moveGenerator_tests, wrong_pos_3_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::string fen = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1";
    engine.Position (fen);
    engine.MakeSanitaryMove (chess::moves::string2move ("c4c5"));
    engine.MakeSanitaryMove (chess::moves::string2move ("c7c6"));
    engine.MakeSanitaryMove (chess::moves::string2move ("e4e5"));
    engine.MakeSanitaryMove (chess::moves::string2move ("d7d5"));
    chess::consts::bitboard perftresults = 1655;
    std::cout << fen << std::endl << engine.LegalMoves () << std::endl;
    chess::consts::bitboard res = engine.Perft (2);
    EXPECT_EQ (perftresults, res);
}

TEST (moveGenerator_tests, wrong_pos_4_test)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::string fen = "r3k2r/Pppp1ppp/1b3nbN/nP6/BBP1P3/q4N2/Pp1P2PP/R2Q1RK1 w kq - 0 1";
    engine.Position (fen);
    engine.MakeSanitaryMove (chess::moves::string2move ("c4c5"));
    engine.MakeSanitaryMove (chess::moves::string2move ("c7c6"));
    engine.MakeSanitaryMove (chess::moves::string2move ("b5c6"));
    engine.MakeSanitaryMove (chess::moves::string2move ("f6g8"));
    engine.MakeSanitaryMove (chess::moves::string2move ("c6c7"));
    chess::consts::bitboard perftresults = 37;
    std::cout << fen << std::endl << engine.LegalMoves () << std::endl;
    chess::consts::bitboard res = engine.Perft (1);
    EXPECT_EQ (perftresults, res);
}

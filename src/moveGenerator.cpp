#include "moveGenerator.hpp"
#include "Defs.hpp"
#include "engine.hpp"
#include "bitboard.hpp"
#include "moves.hpp"

chess::movegenerator::MoveGenerator::MoveGenerator () { initMasks (); }

std::vector<chess::consts::move>
chess::movegenerator::MoveGenerator::GetLegalMoves (chess::engine::Engine &engine)
{
    std::vector<chess::consts::move> legalMoves;
    chess::board::Board board = engine.GetBoard ();
    std::array<chess::consts::bitboard, 12> pieceBoards = board.get_piece_boards ();
    std::array<chess::consts::bitboard, 2> colorBoards = board.get_color_boards ();
    chess::consts::bitboard blockerBoard = colorBoards[0] | colorBoards[1];
    chess::consts::bitboard n_blockerBoard = ~blockerBoard;
    bool white_to_play = board.white_to_play ();
    uint colorOffset = white_to_play ? 0 : 6;

    // Pawns
    chess::consts::bitboard pawnBoard = pieceBoards[0 + colorOffset];
    chess::consts::bitboard singlePushs, doublePushs;
    if (white_to_play)
        {
            singlePushs = (pawnBoard >> 8) & n_blockerBoard;
            doublePushs = ((((pawnBoard & rankMasks[1]) >> 8) & n_blockerBoard) >> 8) & n_blockerBoard;
            std::cout << chess::bitboard_helper::visualize_bitboard (rankMasks[1]) << std::endl;
            while (singlePushs > 0)
                {
                    uint to = chess::bitboard_helper::pop_lsb (singlePushs);
                    uint from = to + 8;
                    legalMoves.push_back (chess::moves ::move_ (from, to));
                }
            while (doublePushs > 0)
                {
                    uint to = chess::bitboard_helper::pop_lsb (doublePushs);
                    uint from = to + 16;
                    legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }
    else
        {
            singlePushs = (pawnBoard << 8) & n_blockerBoard;
            doublePushs = ((((pawnBoard & rankMasks[7]) << 8) & n_blockerBoard) << 8) & n_blockerBoard;
            while (singlePushs > 0)
                {
                    uint to = chess::bitboard_helper::pop_lsb (singlePushs);
                    uint from = to - 8;
                    legalMoves.push_back (chess::moves ::move_ (from, to));
                }
            while (doublePushs > 0)
                {
                    uint to = chess::bitboard_helper::pop_lsb (doublePushs);
                    uint from = to - 16;
                    legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }

    return legalMoves;
}

void
chess::movegenerator::MoveGenerator::initMasks ()
{
    chess::consts::bitboard zeroRankMask = 0xFF00000000000000;
    chess::consts::bitboard zeroFileMask = 0x0101010101010101;

    for (uint i = 0; i < 8; i++)
        {
            rankMasks[i] = zeroRankMask >> (8 * i);
            fileMasks[i] = zeroFileMask >> (8 * i);
        }
}

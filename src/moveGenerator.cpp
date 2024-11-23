#include "moveGenerator.hpp"
#include "Defs.hpp"
#include "engine.hpp"
#include "bitboard.hpp"
#include "moves.hpp"

chess::movegenerator::MoveGenerator::MoveGenerator ()
{
    initMasks ();
    initKnightMoves ();
}

std::vector<chess::consts::move>
chess::movegenerator::MoveGenerator::GetLegalMoves (chess::engine::Engine &engine)
{
    std::vector<chess::consts::move> legalMoves;
    chess::board::Board board = engine.GetBoard ();
    std::array<chess::consts::bitboard, 12> pieceBoards = board.get_piece_boards ();
    std::array<chess::consts::bitboard, 2> colorBoards = board.get_color_boards ();
    chess::consts::bitboard ghostboard = board.get_ghost_board ();
    chess::consts::bitboard blockerBoard = colorBoards[0] | colorBoards[1];
    chess::consts::bitboard n_blockerBoard = ~blockerBoard;
    bool white_to_play = board.white_to_play ();
    uint colorOffset = white_to_play ? 0 : 6;
    chess::consts::bitboard myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
    chess::consts::bitboard n_myColorBoard = ~myColorBoard;
    chess::consts::bitboard enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
    chess::consts::bitboard n_enemyColorBoard = ~enemyColorBoard;

    // Pawns
    chess::consts::bitboard pawnBoard = pieceBoards[0 + colorOffset];
    chess::consts::bitboard singlePushs, doublePushs, promotions, captures_left, captures_right;
    chess::consts::bitboard captures_promotions_left, captures_promotions_right;
    uint from_offset = white_to_play ? 8 : -8;
    uint from_double_offset = white_to_play ? 16 : -16;
    uint from_right_offset = white_to_play ? 7 : -9;
    uint from_left_offset = white_to_play ? 9 : -7;
    chess::consts::bitboard n_promo_rank_occ = pawnBoard & (white_to_play ? n_rankMasks[6] : n_rankMasks[1]);
    chess::consts::bitboard promo_rank_occ = pawnBoard & (white_to_play ? rankMasks[6] : rankMasks[1]);
    chess::consts::bitboard double_rank_occ = pawnBoard & (white_to_play ? rankMasks[1] : rankMasks[6]);

    if (white_to_play)
        {
            singlePushs = (n_promo_rank_occ >> 8) & n_blockerBoard;
            doublePushs = (((double_rank_occ >> 8) & n_blockerBoard) >> 8) & n_blockerBoard;
            promotions = (promo_rank_occ >> 8) & n_blockerBoard;
            captures_right = ((n_promo_rank_occ & n_fileMasks[7]) >> 7) & (colorBoards[1] | ghostboard);
            captures_left = ((n_promo_rank_occ & n_fileMasks[0]) >> 9) & (colorBoards[1] | ghostboard);
            captures_promotions_right = ((promo_rank_occ & n_fileMasks[7]) >> 7) & colorBoards[1];
            captures_promotions_left = ((promo_rank_occ & n_fileMasks[0]) >> 9) & colorBoards[1];
        }
    else
        {
            singlePushs = (n_promo_rank_occ << 8) & n_blockerBoard;
            doublePushs = (((double_rank_occ << 8) & n_blockerBoard) << 8) & n_blockerBoard;
            promotions = (promo_rank_occ << 8) & n_blockerBoard;
            captures_right = ((n_promo_rank_occ & n_fileMasks[7]) << 9) & (colorBoards[0] | ghostboard);
            captures_left = ((n_promo_rank_occ & n_fileMasks[0]) << 7) & (colorBoards[0] | ghostboard);
            captures_promotions_right = ((promo_rank_occ & n_fileMasks[7]) << 9) & colorBoards[0];
            captures_promotions_left = ((promo_rank_occ & n_fileMasks[0]) << 7) & colorBoards[0];
        }
    while (singlePushs > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (singlePushs);
            uint from = to + from_offset;
            legalMoves.push_back (chess::moves ::move_ (from, to));
        }
    while (doublePushs > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (doublePushs);
            uint from = to + from_double_offset;
            legalMoves.push_back (chess::moves::move_ (from, to));
        }
    while (promotions > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (promotions);
            uint from = to + from_offset;
            for (uint piece = 7; piece < 11; piece++)
                {
                    legalMoves.push_back (chess::moves::move_ (from, to, piece));
                }
        }
    while (captures_right > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (captures_right);
            uint from = to + from_right_offset;
            legalMoves.push_back (chess::moves::move_ (from, to));
        }
    while (captures_left > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (captures_left);
            uint from = to + from_left_offset;
            legalMoves.push_back (chess::moves::move_ (from, to));
        }
    while (captures_promotions_right > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (captures_promotions_right);
            uint from = to + from_right_offset;
            for (uint piece = 7; piece < 11; piece++)
                {
                    legalMoves.push_back (chess::moves::move_ (from, to, piece));
                }
        }
    while (captures_promotions_left > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (captures_promotions_left);
            uint from = to + from_left_offset;
            for (uint piece = 7; piece < 11; piece++)
                {
                    legalMoves.push_back (chess::moves::move_ (from, to, piece));
                }
        }

    // Knights
    chess::consts::bitboard knightBoard = pieceBoards[1 + colorOffset];
    while (knightBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (knightBoard);
            chess::consts::bitboard moves = knightMoves[from] & n_myColorBoard;
            while (moves > 0)
                {
                    uint to = chess::bitboard_helper::pop_lsb (moves);
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
            fileMasks[i] = zeroFileMask << (i);
            n_rankMasks[i] = ~rankMasks[i];
            n_fileMasks[i] = ~fileMasks[i];
        }
}

void
chess::movegenerator::MoveGenerator::initKnightMoves ()
{
    chess::consts::bitboard knightPosition = (chess::consts::bitboard)0;
    chess::consts::bitboard north_east_mask = ~(rankMasks[6] | rankMasks[7] | fileMasks[7]);
    chess::consts::bitboard east_north_mask = ~(rankMasks[7] | fileMasks[6] | fileMasks[7]);
    chess::consts::bitboard east_south_mask = ~(rankMasks[0] | fileMasks[6] | fileMasks[7]);
    chess::consts::bitboard south_east_mask = ~(rankMasks[0] | rankMasks[1] | fileMasks[7]);
    chess::consts::bitboard south_west_mask = ~(rankMasks[0] | rankMasks[1] | fileMasks[0]);
    chess::consts::bitboard west_south_mask = ~(rankMasks[0] | fileMasks[0] | fileMasks[1]);
    chess::consts::bitboard west_north_mask = ~(rankMasks[7] | fileMasks[0] | fileMasks[1]);
    chess::consts::bitboard north_west_mask = ~(rankMasks[6] | rankMasks[7] | fileMasks[0]);
    for (uint i = 0; i < 64; i++)
        {
            knightPosition = (chess::consts::bitboard)1 << i;
            chess::consts::bitboard north_east = (knightPosition & north_east_mask) >> 15;
            chess::consts::bitboard east_north = (knightPosition & east_north_mask) >> 6;
            chess::consts::bitboard east_south = (knightPosition & east_south_mask) << 10;
            chess::consts::bitboard south_east = (knightPosition & south_east_mask) << 17;
            chess::consts::bitboard south_west = (knightPosition & south_west_mask) << 15;
            chess::consts::bitboard west_south = (knightPosition & west_south_mask) << 6;
            chess::consts::bitboard west_north = (knightPosition & west_north_mask) >> 10;
            chess::consts::bitboard north_west = (knightPosition & north_west_mask) >> 17;
            knightMoves[i] = north_east | east_north | east_south | south_east | south_west | west_south | west_north | north_west;
        }
}

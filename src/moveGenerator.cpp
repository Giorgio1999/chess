#include "moveGenerator.hpp"
#include "Defs.hpp"
#include "engine.hpp"
#include "bitboard.hpp"
#include "moves.hpp"
#include "magicData.hpp"

chess::movegenerator::MoveGenerator::MoveGenerator ()
{
    initMasks ();
    initKnightMoves ();
    initRookMoves ();
    initKingMoves ();
    initBishopMoves ();
}

std::vector<chess::consts::move>
chess::movegenerator::MoveGenerator::GetLegalMoves (chess::engine::Engine &engine)
{
    std::vector<chess::consts::move> pseudo_legalMoves;
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
    chess::consts::bitboard enemyAttacks = GetAttacks (engine, !white_to_play);

    // Pawns
    chess::consts::bitboard pawnBoard = pieceBoards[0 + colorOffset];
    chess::consts::bitboard singlePushs, doublePushs, promotions, captures_left, captures_right, captures_right_enp, captures_left_enp;
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
            captures_right = ((n_promo_rank_occ & n_fileMasks[7]) >> 7) & colorBoards[1];
            captures_left = ((n_promo_rank_occ & n_fileMasks[0]) >> 9) & colorBoards[1];
            captures_promotions_right = ((promo_rank_occ & n_fileMasks[7]) >> 7) & colorBoards[1];
            captures_promotions_left = ((promo_rank_occ & n_fileMasks[0]) >> 9) & colorBoards[1];
            captures_right_enp = ((n_promo_rank_occ & n_fileMasks[7]) >> 7) & ghostboard;
            captures_left_enp = ((n_promo_rank_occ & n_fileMasks[0]) >> 9) & ghostboard;
            ghostboard = ghostboard << 8;
        }
    else
        {
            singlePushs = (n_promo_rank_occ << 8) & n_blockerBoard;
            doublePushs = (((double_rank_occ << 8) & n_blockerBoard) << 8) & n_blockerBoard;
            promotions = (promo_rank_occ << 8) & n_blockerBoard;
            captures_right = ((n_promo_rank_occ & n_fileMasks[7]) << 9) & colorBoards[0];
            captures_left = ((n_promo_rank_occ & n_fileMasks[0]) << 7) & colorBoards[0];
            captures_promotions_right = ((promo_rank_occ & n_fileMasks[7]) << 9) & colorBoards[0];
            captures_promotions_left = ((promo_rank_occ & n_fileMasks[0]) << 7) & colorBoards[0];
            captures_right_enp = ((n_promo_rank_occ & n_fileMasks[7]) << 9) & ghostboard;
            captures_left_enp = ((n_promo_rank_occ & n_fileMasks[0]) << 7) & ghostboard;
            ghostboard = ghostboard >> 8;
        }
    while (singlePushs > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (singlePushs);
            uint from = to + from_offset;
            pseudo_legalMoves.push_back (chess::moves ::move_ (from, to));
        }
    while (doublePushs > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (doublePushs);
            uint from = to + from_double_offset;
            pseudo_legalMoves.push_back (chess::moves::move_ (from, to));
        }
    while (promotions > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (promotions);
            uint from = to + from_offset;
            for (uint piece = 7; piece < 11; piece++)
                {
                    pseudo_legalMoves.push_back (chess::moves::move_ (from, to, piece));
                }
        }
    while (captures_right > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (captures_right);
            uint from = to + from_right_offset;
            pseudo_legalMoves.push_back (chess::moves::move_ (from, to));
        }
    while (captures_left > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (captures_left);
            uint from = to + from_left_offset;
            pseudo_legalMoves.push_back (chess::moves::move_ (from, to));
        }
    while (captures_promotions_right > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (captures_promotions_right);
            uint from = to + from_right_offset;
            for (uint piece = 7; piece < 11; piece++)
                {
                    pseudo_legalMoves.push_back (chess::moves::move_ (from, to, piece));
                }
        }
    while (captures_promotions_left > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (captures_promotions_left);
            uint from = to + from_left_offset;
            for (uint piece = 7; piece < 11; piece++)
                {
                    pseudo_legalMoves.push_back (chess::moves::move_ (from, to, piece));
                }
        }
    while (captures_right_enp > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (captures_right_enp);
            uint from = to + from_right_offset;
            int ghostsquare = chess::bitboard_helper::pop_lsb (ghostboard);
            pseudo_legalMoves.push_back (chess::moves::move_ (from, to, ghostsquare, true));
        }
    while (captures_left_enp > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (captures_left_enp);
            uint from = to + from_left_offset;
            int ghostsquare = chess::bitboard_helper::pop_lsb (ghostboard);
            pseudo_legalMoves.push_back (chess::moves::move_ (from, to, ghostsquare, true));
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
                    pseudo_legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }

    // Bishops
    chess::consts::bitboard bishopBoard = pieceBoards[2 + colorOffset];
    while (bishopBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (bishopBoard);
            chess::consts::bitboard occupation = blockerBoard & chess::data::relevantoccupancy_masks_bishop[from];
            chess::consts::bitboard moves = chess::data::bishopMoves[from][(occupation * chess::data::magics_bishop[from]) >> (64 - chess::data::width_bishop)] & n_myColorBoard;
            while (moves > 0)
                {
                    uint to = chess::bitboard_helper::pop_lsb (moves);
                    pseudo_legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }

    // Rooks
    chess::consts::bitboard rookBoard = pieceBoards[3 + colorOffset];
    while (rookBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (rookBoard);
            chess::consts::bitboard occupation = blockerBoard & chess::data::relevantoccupancy_masks_rook[from];
            chess::consts::bitboard moves = chess::data::rookMoves[from][(occupation * chess::data::magics_rook[from]) >> (64 - chess::data::width_rook)] & n_myColorBoard;
            while (moves > 0)
                {
                    uint to = chess::bitboard_helper::pop_lsb (moves);
                    pseudo_legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }

    // Queens
    chess::consts::bitboard queenBoard = pieceBoards[4 + colorOffset];
    while (queenBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (queenBoard);
            chess::consts::bitboard occupation = blockerBoard & chess::data::relevantoccupancy_masks_bishop[from];
            chess::consts::bitboard moves = chess::data::bishopMoves[from][(occupation * chess::data::magics_bishop[from]) >> (64 - chess::data::width_bishop)] & n_myColorBoard;
            occupation = blockerBoard & chess::data::relevantoccupancy_masks_rook[from];
            moves |= chess::data::rookMoves[from][(occupation * chess::data::magics_rook[from]) >> (64 - chess::data::width_rook)] & n_myColorBoard;
            while (moves > 0)
                {
                    uint to = chess::bitboard_helper::pop_lsb (moves);
                    pseudo_legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }

    // Kings
    chess::consts::bitboard kingBoard = pieceBoards[5 + colorOffset];
    while (kingBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (kingBoard);
            chess::consts::bitboard moves = kingMoves[from] & n_myColorBoard;
            /*moves &= ~enemyAttacks;*/
            while (moves > 0)
                {
                    uint to = chess::bitboard_helper::pop_lsb (moves);
                    pseudo_legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }

    // Remove illegal moves
    std::vector<chess::consts::move> legalMoves;
    for (chess::consts::move &pseudo_move : pseudo_legalMoves)
        {
            engine.MakeMove (pseudo_move);
            chess::consts::bitboard kingBoard_copy = engine.GetBoard ().get_piece_boards ()[5 + colorOffset];
            chess::consts::bitboard virtual_attacks = GetAttacks (engine, !white_to_play);
            engine.UndoMove ();
            if ((virtual_attacks & kingBoard_copy) == 0)
                {
                    legalMoves.push_back (pseudo_move);
                }
        }

    // Kings castling
    bool castleking = white_to_play ? board.castling ().K : board.castling ().k;
    bool castlequeen = white_to_play ? board.castling ().Q : board.castling ().q;
    if (castleking)
        {
            chess::consts::bitboard castlemask_attacks = white_to_play ? 0x7000000000000000 : 0x0000000000000070;
            chess::consts::bitboard castlemask_occupations = white_to_play ? 0x6000000000000000 : 0x0000000000000060;
            chess::consts::bitboard n_cancastle = (enemyAttacks & castlemask_attacks) | (blockerBoard & castlemask_occupations);
            if (n_cancastle == 0)
                {
                    uint from = white_to_play ? 60 : 4;
                    uint to = white_to_play ? 62 : 6;
                    legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }
    if (castlequeen)
        {
            chess::consts::bitboard castlemask_attacks = white_to_play ? 0x1C00000000000000 : 0x000000000000001C;
            chess::consts::bitboard castlemask_occupations = white_to_play ? 0x0E00000000000000 : 0x000000000000000E;
            chess::consts::bitboard n_cancastle = (enemyAttacks & castlemask_attacks) | (blockerBoard & castlemask_occupations);
            if (n_cancastle == 0)
                {
                    uint from = white_to_play ? 60 : 4;
                    uint to = white_to_play ? 58 : 2;
                    legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }

    return legalMoves;
}

chess::consts::bitboard
chess::movegenerator::MoveGenerator::GetAttacks (chess::engine::Engine &engine, const bool &white_to_play)
{
    chess::consts::bitboard attacks = (chess::consts::bitboard)0;

    chess::board::Board board = engine.GetBoard ();
    std::array<chess::consts::bitboard, 12> pieceBoards = board.get_piece_boards ();
    std::array<chess::consts::bitboard, 2> colorBoards = board.get_color_boards ();
    chess::consts::bitboard ghostboard = board.get_ghost_board ();
    chess::consts::bitboard blockerBoard = colorBoards[0] | colorBoards[1];
    chess::consts::bitboard n_blockerBoard = ~blockerBoard;
    uint colorOffset = white_to_play ? 0 : 6;
    chess::consts::bitboard myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
    chess::consts::bitboard n_myColorBoard = ~myColorBoard;
    chess::consts::bitboard enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
    chess::consts::bitboard n_enemyColorBoard = ~enemyColorBoard;

    // Pawns
    chess::consts::bitboard pawnBoard = pieceBoards[0 + colorOffset];
    chess::consts::bitboard captures_left, captures_right;
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
            captures_right = ((n_promo_rank_occ & n_fileMasks[7]) >> 7) & (colorBoards[1] | ghostboard);
            captures_left = ((n_promo_rank_occ & n_fileMasks[0]) >> 9) & (colorBoards[1] | ghostboard);
            captures_promotions_right = ((promo_rank_occ & n_fileMasks[7]) >> 7) & colorBoards[1];
            captures_promotions_left = ((promo_rank_occ & n_fileMasks[0]) >> 9) & colorBoards[1];
        }
    else
        {
            captures_right = ((n_promo_rank_occ & n_fileMasks[7]) << 9) & (colorBoards[0] | ghostboard);
            captures_left = ((n_promo_rank_occ & n_fileMasks[0]) << 7) & (colorBoards[0] | ghostboard);
            captures_promotions_right = ((promo_rank_occ & n_fileMasks[7]) << 9) & colorBoards[0];
            captures_promotions_left = ((promo_rank_occ & n_fileMasks[0]) << 7) & colorBoards[0];
        }
    attacks |= captures_right;
    attacks |= captures_left;
    attacks |= captures_promotions_right;
    attacks |= captures_promotions_left;

    // Knights
    chess::consts::bitboard knightBoard = pieceBoards[1 + colorOffset];
    while (knightBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (knightBoard);
            chess::consts::bitboard moves = knightMoves[from] & n_myColorBoard;
            attacks |= moves;
        }

    // Bishops
    chess::consts::bitboard bishopBoard = pieceBoards[2 + colorOffset];
    while (bishopBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (bishopBoard);
            chess::consts::bitboard occupation = blockerBoard & chess::data::relevantoccupancy_masks_bishop[from];
            chess::consts::bitboard moves = chess::data::bishopMoves[from][(occupation * chess::data::magics_bishop[from]) >> (64 - chess::data::width_bishop)] & n_myColorBoard;
            attacks |= moves;
        }

    // Rooks
    chess::consts::bitboard rookBoard = pieceBoards[3 + colorOffset];
    while (rookBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (rookBoard);
            chess::consts::bitboard occupation = blockerBoard & chess::data::relevantoccupancy_masks_rook[from];
            chess::consts::bitboard moves = chess::data::rookMoves[from][(occupation * chess::data::magics_rook[from]) >> (64 - chess::data::width_rook)] & n_myColorBoard;
            attacks |= moves;
        }

    // Queens
    chess::consts::bitboard queenBoard = pieceBoards[4 + colorOffset];
    while (queenBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (queenBoard);
            chess::consts::bitboard occupation = blockerBoard & chess::data::relevantoccupancy_masks_bishop[from];
            chess::consts::bitboard moves = chess::data::bishopMoves[from][(occupation * chess::data::magics_bishop[from]) >> (64 - chess::data::width_bishop)] & n_myColorBoard;
            occupation = blockerBoard & chess::data::relevantoccupancy_masks_rook[from];
            moves |= chess::data::rookMoves[from][(occupation * chess::data::magics_rook[from]) >> (64 - chess::data::width_rook)] & n_myColorBoard;
            attacks |= moves;
        }

    // Kings
    chess::consts::bitboard kingBoard = pieceBoards[5 + colorOffset];
    while (kingBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (kingBoard);
            chess::consts::bitboard moves = kingMoves[from] & n_myColorBoard;
            attacks |= moves;
        }

    return attacks;
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

void
chess::movegenerator::MoveGenerator::initBishopMoves ()
{
    for (uint square = 0; square < 64; square++)
        {
            uint file = square % 8;
            uint rank = (square - file) / 8;
            int distNorthEast = std::min (rank, 7 - file);
            int distSouthEast = std::min (7 - rank, 7 - file);
            int distSouthWest = std::min (7 - rank, file);
            int distNorthWest = std::min (rank, file);
            std::vector<chess::consts::bitboard> occupations = chess::data::occupanciesForEachSquare_bishop[square];
            for (const chess::consts::bitboard &occupation : occupations)
                {
                    chess::consts::bitboard from = (chess::consts::bitboard)1 << square;
                    chess::consts::bitboard shiftmoves = from;
                    chess::consts::bitboard northeast = (chess::consts::bitboard)0;
                    for (uint offset = 0; offset < (uint)distNorthEast; offset++)
                        {
                            shiftmoves = shiftmoves >> 7;
                            northeast |= shiftmoves;
                            shiftmoves |= from;
                            shiftmoves &= ~occupation;
                        }

                    shiftmoves = from;
                    chess::consts::bitboard southeast = (chess::consts::bitboard)0;
                    for (uint offset = 0; offset < (uint)distSouthEast; offset++)
                        {
                            shiftmoves = shiftmoves << 9;
                            southeast |= shiftmoves;
                            shiftmoves |= from;
                            shiftmoves &= ~occupation;
                        }

                    shiftmoves = from;
                    chess::consts::bitboard southwest = (chess::consts::bitboard)0;
                    for (uint offset = 0; offset < (uint)distSouthWest; offset++)
                        {
                            shiftmoves = shiftmoves << 7;
                            southwest |= shiftmoves;
                            shiftmoves |= from;
                            shiftmoves &= ~occupation;
                        }

                    shiftmoves = from;
                    chess::consts::bitboard northwest = (chess::consts::bitboard)0;
                    for (uint offset = 0; offset < (uint)distNorthWest; offset++)
                        {
                            shiftmoves = shiftmoves >> 9;
                            northwest |= shiftmoves;
                            shiftmoves |= from;
                            shiftmoves &= ~occupation;
                        }
                    chess::consts::bitboard moves = northeast | southeast | southwest | northwest;
                    chess::data::bishopMoves[square][(occupation * chess::data::magics_bishop[square]) >> (64 - chess::data::width_bishop)] = moves;
                }
        }
}

void
chess::movegenerator::MoveGenerator::initRookMoves ()
{
    for (uint square = 0; square < 64; square++)
        {
            uint file = square % 8;
            uint rank = (square - file) / 8;
            int distNorth = rank;
            int distSouth = 7 - rank;
            int distEast = 7 - file;
            int distWest = file;
            std::vector<chess::consts::bitboard> occupations = chess::data::occupanciesForEachSquare_rook[square];
            for (const chess::consts::bitboard &occupation : occupations)
                {
                    chess::consts::bitboard from = (chess::consts::bitboard)1 << square;
                    chess::consts::bitboard shiftmoves = from;
                    chess::consts::bitboard north = (chess::consts::bitboard)0;
                    for (uint offset = 0; offset < (uint)distNorth; offset++)
                        {
                            shiftmoves = shiftmoves >> 8;
                            north |= shiftmoves;
                            shiftmoves |= (chess::consts::bitboard)1 << square;
                            shiftmoves &= ~occupation;
                        }
                    shiftmoves = from;
                    chess::consts::bitboard east = (chess::consts::bitboard)0;
                    for (uint offset = 0; offset < (uint)distEast; offset++)
                        {
                            shiftmoves = shiftmoves << 1;
                            east |= shiftmoves;
                            shiftmoves |= (chess::consts::bitboard)1 << square;
                            shiftmoves &= ~occupation;
                        }
                    shiftmoves = from;
                    chess::consts::bitboard south = (chess::consts::bitboard)0;
                    for (uint offset = 0; offset < (uint)distSouth; offset++)
                        {
                            shiftmoves = shiftmoves << 8;
                            south |= shiftmoves;
                            shiftmoves |= (chess::consts::bitboard)1 << square;
                            shiftmoves &= ~occupation;
                        }
                    shiftmoves = from;
                    chess::consts::bitboard west = (chess::consts::bitboard)0;
                    for (uint offset = 0; offset < (uint)distWest; offset++)
                        {
                            shiftmoves = shiftmoves >> 1;
                            west |= shiftmoves;
                            shiftmoves |= (chess::consts::bitboard)1;
                            shiftmoves &= ~occupation;
                        }
                    chess::consts::bitboard moves = north | east | south | west;
                    chess::data::rookMoves[square][(occupation * chess::data::magics_rook[square]) >> (64 - chess::data::width_rook)] = moves;
                }
        }
}

void
chess::movegenerator::MoveGenerator::initKingMoves ()
{
    chess::consts::bitboard kingPosition = (chess::consts::bitboard)0;
    chess::consts::bitboard north_mask = ~rankMasks[7];
    chess::consts::bitboard east_mask = ~fileMasks[7];
    chess::consts::bitboard south_mask = ~rankMasks[0];
    chess::consts::bitboard west_mask = ~fileMasks[0];
    for (uint i = 0; i < 64; i++)
        {
            kingPosition = (chess::consts::bitboard)1 << i;
            chess::consts::bitboard north = (kingPosition & north_mask) >> 8;
            chess::consts::bitboard north_east = ((kingPosition & north_mask) & east_mask) >> 7;
            chess::consts::bitboard east = (kingPosition & east_mask) << 1;
            chess::consts::bitboard south_east = ((kingPosition & south_mask) & east_mask) << 9;
            chess::consts::bitboard south = (kingPosition & south_mask) << 8;
            chess::consts::bitboard south_west = ((kingPosition & south_mask) & west_mask) << 7;
            chess::consts::bitboard west = (kingPosition & west_mask) >> 1;
            chess::consts::bitboard north_west = ((kingPosition & north_mask) & west_mask) >> 9;
            kingMoves[i] = north | north_east | east | south_east | south | south_west | west | north_west;
        }
}

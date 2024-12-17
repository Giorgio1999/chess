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

void
chess::movegenerator::MoveGenerator::fillPawnMoves (chess::consts::bitboard pawnBoard, std::vector<chess::consts::move> &pseudo_legalMoves)
{
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
    chess::consts::bitboard ghostcopy = ghostboard;
    while (captures_right_enp > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (captures_right_enp);
            uint from = to + from_right_offset;
            int ghostsquare = chess::bitboard_helper::pop_lsb (ghostcopy);
            pseudo_legalMoves.push_back (chess::moves::move_ (from, to, ghostsquare, true));
        }
    ghostcopy = ghostboard;
    while (captures_left_enp > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (captures_left_enp);
            uint from = to + from_left_offset;
            int ghostsquare = chess::bitboard_helper::pop_lsb (ghostcopy);
            pseudo_legalMoves.push_back (chess::moves::move_ (from, to, ghostsquare, true));
        }
}

void
chess::movegenerator::MoveGenerator::fillKnightMoves (chess::consts::bitboard knightBoard, std::vector<chess::consts::move> &pseudo_legalMoves)
{
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
}

void
chess::movegenerator::MoveGenerator::fillBishopMoves (chess::consts::bitboard bishopBoard, std::vector<chess::consts::move> &pseudo_legalMoves)
{
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
}

void
chess::movegenerator::MoveGenerator::fillRookMoves (chess::consts::bitboard rookBoard, std::vector<chess::consts::move> &pseudo_legalMoves)
{
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
}

void
chess::movegenerator::MoveGenerator::fillQueenMoves (chess::consts::bitboard queenBoard, std::vector<chess::consts::move> &pseudo_legalMoves)
{
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
}

void
chess::movegenerator::MoveGenerator::fillKingMoves (chess::consts::bitboard kingBoard, std::vector<chess::consts::move> &pseudo_legalMoves)
{
    while (kingBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (kingBoard);
            chess::consts::bitboard moves = kingMoves[from] & n_myColorBoard;
            while (moves > 0)
                {
                    uint to = chess::bitboard_helper::pop_lsb (moves);
                    pseudo_legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }
}

void
chess::movegenerator::MoveGenerator::fillCastlingMoves (chess::engine::Engine &engine, std::vector<chess::consts::move> &legalMoves)
{
    bool castleking = white_to_play ? board.castling ().K : board.castling ().k;
    bool castlequeen = white_to_play ? board.castling ().Q : board.castling ().q;
    if (castleking)
        {
            chess::consts::bitboard castlemask_occupations = white_to_play ? 0x6000000000000000 : 0x0000000000000060;
            chess::consts::bitboard n_cancastle = (blockerBoard & castlemask_occupations);
            chess::consts::Square castleSquare_G = white_to_play ? chess::consts::Square::G1 : chess::consts::Square::G8;
            chess::consts::Square castleSquare_F = white_to_play ? chess::consts::Square::F1 : chess::consts::Square::F8;
            chess::consts::Square castleSquare_E = white_to_play ? chess::consts::Square::E1 : chess::consts::Square::E8;
            if (n_cancastle == 0 && !IsSquareAttacked (engine, !white_to_play, castleSquare_E) && !IsSquareAttacked (engine, !white_to_play, castleSquare_F) && !IsSquareAttacked (engine, !white_to_play, castleSquare_G))
                {
                    uint from = white_to_play ? 60 : 4;
                    uint to = white_to_play ? 62 : 6;
                    legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }
    if (castlequeen)
        {
            chess::consts::bitboard castlemask_occupations = white_to_play ? 0x0E00000000000000 : 0x000000000000000E;
            chess::consts::bitboard n_cancastle = blockerBoard & castlemask_occupations;
            chess::consts::Square castleSquare_E = white_to_play ? chess::consts::Square::E1 : chess::consts::Square::E8;
            chess::consts::Square castleSquare_D = white_to_play ? chess::consts::Square::D1 : chess::consts::Square::D8;
            chess::consts::Square castleSquare_C = white_to_play ? chess::consts::Square::C1 : chess::consts::Square::C8;
            if (n_cancastle == 0 && !IsSquareAttacked (engine, !white_to_play, castleSquare_E) && !IsSquareAttacked (engine, !white_to_play, castleSquare_D) && !IsSquareAttacked (engine, !white_to_play, castleSquare_C))
                {
                    uint from = white_to_play ? 60 : 4;
                    uint to = white_to_play ? 58 : 2;
                    legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }
}

void
chess::movegenerator::MoveGenerator::filterIllegalMoves (chess::engine::Engine &engine, std::vector<chess::consts::move> &pseudo_legalMoves, std::vector<chess::consts::move> &legalMoves)
{
    for (chess::consts::move &pseudo_move : pseudo_legalMoves)
        {
            engine.MakeMove (pseudo_move);
            chess::consts::bitboard kingBoard_copy = engine.GetBoard ().get_piece_boards ()[5 + colorOffset];
            if (!IsSquareAttacked (engine, !white_to_play, (chess::consts::Square)chess::bitboard_helper::pop_lsb (kingBoard_copy)))
                {
                    legalMoves.push_back (pseudo_move);
                }
            engine.UndoMove ();
        }
}

std::vector<chess::consts::move> &
chess::movegenerator::MoveGenerator::GetLegalMoves (chess::engine::Engine &engine)
{
    persistent_pseudo_legalMoves.clear ();
    persistent_pseudo_legalMoves.reserve (218);
    board = engine.GetBoard ();
    pieceBoards = board.get_piece_boards ();
    colorBoards = board.get_color_boards ();
    ghostboard = board.get_ghost_board ();
    blockerBoard = colorBoards[0] | colorBoards[1];
    n_blockerBoard = ~blockerBoard;
    white_to_play = board.white_to_play ();
    colorOffset = white_to_play ? 0 : 6;
    myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
    n_myColorBoard = ~myColorBoard;
    enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
    n_enemyColorBoard = ~enemyColorBoard;

    // Pawns
    fillPawnMoves (pieceBoards[0 + colorOffset], persistent_pseudo_legalMoves);

    // Knights
    fillKnightMoves (pieceBoards[1 + colorOffset], persistent_pseudo_legalMoves);

    // Bishops
    fillBishopMoves (pieceBoards[2 + colorOffset], persistent_pseudo_legalMoves);

    // Rooks
    fillRookMoves (pieceBoards[3 + colorOffset], persistent_pseudo_legalMoves);

    // Queens
    fillQueenMoves (pieceBoards[4 + colorOffset], persistent_pseudo_legalMoves);

    // Kings
    fillKingMoves (pieceBoards[5 + colorOffset], persistent_pseudo_legalMoves);

    // Remove illegal moves
    persistent_legalMoves.clear ();
    persistent_legalMoves.reserve (218);
    filterIllegalMoves (engine, persistent_pseudo_legalMoves, persistent_legalMoves);

    // Kings castling
    fillCastlingMoves (engine, persistent_legalMoves);

    return persistent_legalMoves;
}

void
chess::movegenerator::MoveGenerator::fillPawnAttacks (chess::consts::bitboard pawnBoard, chess::consts::bitboard &attacks)
{
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
            captures_right = ((n_promo_rank_occ & n_fileMasks[7]) >> 7);
            captures_left = ((n_promo_rank_occ & n_fileMasks[0]) >> 9);
            captures_promotions_right = ((promo_rank_occ & n_fileMasks[7]) >> 7);
            captures_promotions_left = ((promo_rank_occ & n_fileMasks[0]) >> 9);
        }
    else
        {
            captures_right = ((n_promo_rank_occ & n_fileMasks[7]) << 9);
            captures_left = ((n_promo_rank_occ & n_fileMasks[0]) << 7);
            captures_promotions_right = ((promo_rank_occ & n_fileMasks[7]) << 9);
            captures_promotions_left = ((promo_rank_occ & n_fileMasks[0]) << 7);
        }
    attacks |= captures_right;
    attacks |= captures_left;
    attacks |= captures_promotions_right;
    attacks |= captures_promotions_left;
}

void
chess::movegenerator::MoveGenerator::fillKnightAttacks (chess::consts::bitboard knightBoard, chess::consts::bitboard &attacks)
{
    while (knightBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (knightBoard);
            chess::consts::bitboard moves = knightMoves[from] & n_myColorBoard;
            attacks |= moves;
        }
}

void
chess::movegenerator::MoveGenerator::fillBishopAttacks (chess::consts::bitboard bishopBoard, chess::consts::bitboard &attacks)
{
    while (bishopBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (bishopBoard);
            chess::consts::bitboard occupation = blockerBoard & chess::data::relevantoccupancy_masks_bishop[from];
            chess::consts::bitboard moves = chess::data::bishopMoves[from][(occupation * chess::data::magics_bishop[from]) >> (64 - chess::data::width_bishop)] & n_myColorBoard;
            attacks |= moves;
        }
}

void
chess::movegenerator::MoveGenerator::fillRookAttacks (chess::consts::bitboard rookBoard, chess::consts::bitboard &attacks)
{
    while (rookBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (rookBoard);
            chess::consts::bitboard occupation = blockerBoard & chess::data::relevantoccupancy_masks_rook[from];
            chess::consts::bitboard moves = chess::data::rookMoves[from][(occupation * chess::data::magics_rook[from]) >> (64 - chess::data::width_rook)] & n_myColorBoard;
            attacks |= moves;
        }
}

void
chess::movegenerator::MoveGenerator::fillQueenAttacks (chess::consts::bitboard queenBoard, chess::consts::bitboard &attacks)
{
    while (queenBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (queenBoard);
            chess::consts::bitboard occupation = blockerBoard & chess::data::relevantoccupancy_masks_bishop[from];
            chess::consts::bitboard moves = chess::data::bishopMoves[from][(occupation * chess::data::magics_bishop[from]) >> (64 - chess::data::width_bishop)] & n_myColorBoard;
            occupation = blockerBoard & chess::data::relevantoccupancy_masks_rook[from];
            moves |= chess::data::rookMoves[from][(occupation * chess::data::magics_rook[from]) >> (64 - chess::data::width_rook)] & n_myColorBoard;
            attacks |= moves;
        }
}

void
chess::movegenerator::MoveGenerator::fillKingAttacks (chess::consts::bitboard kingBoard, chess::consts::bitboard &attacks)
{
    while (kingBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (kingBoard);
            chess::consts::bitboard moves = kingMoves[from] & n_myColorBoard;
            attacks |= moves;
        }
}

chess::consts::bitboard
chess::movegenerator::MoveGenerator::GetAttacks (chess::engine::Engine &engine, const bool &_white_to_play)
{
    chess::consts::bitboard attacks = (chess::consts::bitboard)0;

    board = engine.GetBoard ();
    pieceBoards = board.get_piece_boards ();
    colorBoards = board.get_color_boards ();
    ghostboard = board.get_ghost_board ();
    blockerBoard = colorBoards[0] | colorBoards[1];
    n_blockerBoard = ~blockerBoard;
    white_to_play = _white_to_play;
    colorOffset = white_to_play ? 0 : 6;
    myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
    n_myColorBoard = ~myColorBoard;
    enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
    n_enemyColorBoard = ~enemyColorBoard;

    // Pawns
    chess::consts::bitboard pawnBoard = pieceBoards[0 + colorOffset];
    fillPawnAttacks (pawnBoard, attacks);

    // Knights
    chess::consts::bitboard knightBoard = pieceBoards[1 + colorOffset];
    fillKnightAttacks (knightBoard, attacks);

    // Bishops
    chess::consts::bitboard bishopBoard = pieceBoards[2 + colorOffset];
    fillBishopAttacks (bishopBoard, attacks);

    // Rooks
    chess::consts::bitboard rookBoard = pieceBoards[3 + colorOffset];
    fillRookAttacks (rookBoard, attacks);

    // Queens
    chess::consts::bitboard queenBoard = pieceBoards[4 + colorOffset];
    fillQueenAttacks (queenBoard, attacks);

    // Kings
    chess::consts::bitboard kingBoard = pieceBoards[5 + colorOffset];
    fillKingAttacks (kingBoard, attacks);

    return attacks;
}

chess::consts::bitboard
chess::movegenerator::MoveGenerator::GetAttacks (chess::engine::Engine &engine, const chess::consts::Piece piece, const int square)
{
    chess::consts::bitboard attacks = (chess::consts::bitboard)0;
    chess::consts::bitboard pieceBoard = (chess::consts::bitboard)1 << square;

    board = engine.GetBoard ();
    pieceBoards = board.get_piece_boards ();
    colorBoards = board.get_color_boards ();
    ghostboard = board.get_ghost_board ();
    blockerBoard = colorBoards[0] | colorBoards[1];
    n_blockerBoard = ~blockerBoard;

    switch (piece)
        {
        case chess::consts::empty:
            break;
        case chess::consts::P:
            white_to_play = true;
            colorOffset = white_to_play ? 0 : 6;
            myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
            n_myColorBoard = ~myColorBoard;
            enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
            n_enemyColorBoard = ~enemyColorBoard;
            fillPawnAttacks (pieceBoard, attacks);

            break;
        case chess::consts::N:
            white_to_play = true;
            colorOffset = white_to_play ? 0 : 6;
            myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
            n_myColorBoard = ~myColorBoard;
            enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
            n_enemyColorBoard = ~enemyColorBoard;
            fillKnightAttacks (pieceBoard, attacks);

            break;
        case chess::consts::B:
            white_to_play = true;
            colorOffset = white_to_play ? 0 : 6;
            myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
            n_myColorBoard = ~myColorBoard;
            enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
            n_enemyColorBoard = ~enemyColorBoard;
            fillBishopAttacks (pieceBoard, attacks);

            break;
        case chess::consts::R:
            white_to_play = true;
            colorOffset = white_to_play ? 0 : 6;
            myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
            n_myColorBoard = ~myColorBoard;
            enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
            n_enemyColorBoard = ~enemyColorBoard;
            fillRookAttacks (pieceBoard, attacks);

            break;
        case chess::consts::Q:
            white_to_play = true;
            colorOffset = white_to_play ? 0 : 6;
            myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
            n_myColorBoard = ~myColorBoard;
            enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
            n_enemyColorBoard = ~enemyColorBoard;
            fillQueenAttacks (pieceBoard, attacks);

            break;
        case chess::consts::K:
            white_to_play = true;
            colorOffset = white_to_play ? 0 : 6;
            myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
            n_myColorBoard = ~myColorBoard;
            enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
            n_enemyColorBoard = ~enemyColorBoard;
            fillKingAttacks (pieceBoard, attacks);

            break;
        case chess::consts::p:
            white_to_play = false;
            colorOffset = white_to_play ? 0 : 6;
            myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
            n_myColorBoard = ~myColorBoard;
            enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
            n_enemyColorBoard = ~enemyColorBoard;
            fillPawnAttacks (pieceBoard, attacks);

            break;
        case chess::consts::n:
            white_to_play = false;
            colorOffset = white_to_play ? 0 : 6;
            myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
            n_myColorBoard = ~myColorBoard;
            enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
            n_enemyColorBoard = ~enemyColorBoard;
            fillKnightAttacks (pieceBoard, attacks);

            break;
        case chess::consts::b:
            white_to_play = false;
            colorOffset = white_to_play ? 0 : 6;
            myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
            n_myColorBoard = ~myColorBoard;
            enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
            n_enemyColorBoard = ~enemyColorBoard;
            fillBishopAttacks (pieceBoard, attacks);

            break;
        case chess::consts::r:
            white_to_play = false;
            colorOffset = white_to_play ? 0 : 6;
            myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
            n_myColorBoard = ~myColorBoard;
            enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
            n_enemyColorBoard = ~enemyColorBoard;
            fillRookAttacks (pieceBoard, attacks);

            break;
        case chess::consts::q:
            white_to_play = false;
            colorOffset = white_to_play ? 0 : 6;
            myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
            n_myColorBoard = ~myColorBoard;
            enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
            n_enemyColorBoard = ~enemyColorBoard;
            fillQueenAttacks (pieceBoard, attacks);

            break;
        case chess::consts::k:
            white_to_play = false;
            colorOffset = white_to_play ? 0 : 6;
            myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
            n_myColorBoard = ~myColorBoard;
            enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
            n_enemyColorBoard = ~enemyColorBoard;
            fillKingAttacks (pieceBoard, attacks);

            break;
        }
    return attacks;
}

void
chess::movegenerator::MoveGenerator::fillPawnCaptures (chess::consts::bitboard pawnBoard, std::vector<chess::consts::move> &pseudo_legalMoves)
{
    chess::consts::bitboard captures_left, captures_right, captures_right_enp, captures_left_enp;
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
            captures_right = ((n_promo_rank_occ & n_fileMasks[7]) << 9) & colorBoards[0];
            captures_left = ((n_promo_rank_occ & n_fileMasks[0]) << 7) & colorBoards[0];
            captures_promotions_right = ((promo_rank_occ & n_fileMasks[7]) << 9) & colorBoards[0];
            captures_promotions_left = ((promo_rank_occ & n_fileMasks[0]) << 7) & colorBoards[0];
            captures_right_enp = ((n_promo_rank_occ & n_fileMasks[7]) << 9) & ghostboard;
            captures_left_enp = ((n_promo_rank_occ & n_fileMasks[0]) << 7) & ghostboard;
            ghostboard = ghostboard >> 8;
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
    chess::consts::bitboard ghostcopy = ghostboard;
    while (captures_right_enp > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (captures_right_enp);
            uint from = to + from_right_offset;
            int ghostsquare = chess::bitboard_helper::pop_lsb (ghostcopy);
            pseudo_legalMoves.push_back (chess::moves::move_ (from, to, ghostsquare, true));
        }
    ghostcopy = ghostboard;
    while (captures_left_enp > 0)
        {
            uint to = chess::bitboard_helper::pop_lsb (captures_left_enp);
            uint from = to + from_left_offset;
            int ghostsquare = chess::bitboard_helper::pop_lsb (ghostcopy);
            pseudo_legalMoves.push_back (chess::moves::move_ (from, to, ghostsquare, true));
        }
}

void
chess::movegenerator::MoveGenerator::fillKnightCaptures (chess::consts::bitboard knightBoard, std::vector<chess::consts::move> &pseudo_legalMoves)
{
    while (knightBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (knightBoard);
            chess::consts::bitboard moves = (knightMoves[from] & n_myColorBoard) & enemyColorBoard;
            while (moves > 0)
                {
                    uint to = chess::bitboard_helper::pop_lsb (moves);
                    pseudo_legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }
}

void
chess::movegenerator::MoveGenerator::fillBishopCaptures (chess::consts::bitboard bishopBoard, std::vector<chess::consts::move> &pseudo_legalMoves)
{
    while (bishopBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (bishopBoard);
            chess::consts::bitboard occupation = blockerBoard & chess::data::relevantoccupancy_masks_bishop[from];
            chess::consts::bitboard moves = (chess::data::bishopMoves[from][(occupation * chess::data::magics_bishop[from]) >> (64 - chess::data::width_bishop)] & n_myColorBoard) & enemyColorBoard;
            while (moves > 0)
                {
                    uint to = chess::bitboard_helper::pop_lsb (moves);
                    pseudo_legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }
}

void
chess::movegenerator::MoveGenerator::fillRookCaptures (chess::consts::bitboard rookBoard, std::vector<chess::consts::move> &pseudo_legalMoves)
{
    while (rookBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (rookBoard);
            chess::consts::bitboard occupation = blockerBoard & chess::data::relevantoccupancy_masks_rook[from];
            chess::consts::bitboard moves = (chess::data::rookMoves[from][(occupation * chess::data::magics_rook[from]) >> (64 - chess::data::width_rook)] & n_myColorBoard) & enemyColorBoard;
            while (moves > 0)
                {
                    uint to = chess::bitboard_helper::pop_lsb (moves);
                    pseudo_legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }
}

void
chess::movegenerator::MoveGenerator::fillQueenCaptures (chess::consts::bitboard queenBoard, std::vector<chess::consts::move> &pseudo_legalMoves)
{
    while (queenBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (queenBoard);
            chess::consts::bitboard occupation = blockerBoard & chess::data::relevantoccupancy_masks_bishop[from];
            chess::consts::bitboard moves = chess::data::bishopMoves[from][(occupation * chess::data::magics_bishop[from]) >> (64 - chess::data::width_bishop)] & n_myColorBoard;
            occupation = blockerBoard & chess::data::relevantoccupancy_masks_rook[from];
            moves |= chess::data::rookMoves[from][(occupation * chess::data::magics_rook[from]) >> (64 - chess::data::width_rook)] & n_myColorBoard;
            moves &= enemyColorBoard;
            while (moves > 0)
                {
                    uint to = chess::bitboard_helper::pop_lsb (moves);
                    pseudo_legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }
}

void
chess::movegenerator::MoveGenerator::fillKingCaptures (chess::consts::bitboard kingBoard, std::vector<chess::consts::move> &pseudo_legalMoves)
{
    while (kingBoard > 0)
        {
            uint from = chess::bitboard_helper::pop_lsb (kingBoard);
            chess::consts::bitboard moves = (kingMoves[from] & n_myColorBoard) & enemyColorBoard;
            while (moves > 0)
                {
                    uint to = chess::bitboard_helper::pop_lsb (moves);
                    pseudo_legalMoves.push_back (chess::moves::move_ (from, to));
                }
        }
}

std::vector<chess::consts::move> &
chess::movegenerator::MoveGenerator::GetLegalCaptures (chess::engine::Engine &engine)
{
    persistent_pseudo_legalMoves.clear ();
    persistent_pseudo_legalMoves.reserve (218);

    board = engine.GetBoard ();
    pieceBoards = board.get_piece_boards ();
    colorBoards = board.get_color_boards ();
    ghostboard = board.get_ghost_board ();
    blockerBoard = colorBoards[0] | colorBoards[1];
    n_blockerBoard = ~blockerBoard;
    white_to_play = board.white_to_play ();
    colorOffset = white_to_play ? 0 : 6;
    myColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
    n_myColorBoard = ~myColorBoard;
    enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
    n_enemyColorBoard = ~enemyColorBoard;

    // Pawns
    chess::consts::bitboard pawnBoard = pieceBoards[0 + colorOffset];
    fillPawnCaptures (pawnBoard, persistent_pseudo_legalMoves);

    // Knights
    chess::consts::bitboard knightBoard = pieceBoards[1 + colorOffset];
    fillKnightCaptures (knightBoard, persistent_pseudo_legalMoves);

    // Bishops
    chess::consts::bitboard bishopBoard = pieceBoards[2 + colorOffset];
    fillBishopCaptures (bishopBoard, persistent_pseudo_legalMoves);

    // Rooks
    chess::consts::bitboard rookBoard = pieceBoards[3 + colorOffset];
    fillRookCaptures (rookBoard, persistent_pseudo_legalMoves);

    // Queens
    chess::consts::bitboard queenBoard = pieceBoards[4 + colorOffset];
    fillQueenCaptures (queenBoard, persistent_pseudo_legalMoves);

    // Kings
    chess::consts::bitboard kingBoard = pieceBoards[5 + colorOffset];
    fillKingCaptures (kingBoard, persistent_pseudo_legalMoves);

    // Remove illegal moves
    persistent_legalMoves.clear ();
    persistent_legalMoves.reserve (persistent_pseudo_legalMoves.size ());
    filterIllegalMoves (engine, persistent_pseudo_legalMoves, persistent_legalMoves);

    return persistent_legalMoves;
}

bool
chess::movegenerator::MoveGenerator::IsSquareAttacked (chess::engine::Engine &engine, const bool &white_to_play, const chess::consts::Square &square)
{
    chess::board::Board board = engine.GetBoard ();
    int colorOffset = white_to_play ? 0 : 6;
    auto pieceBoard = board.get_piece_boards ();
    chess::consts::bitboard pawns = pieceBoard[0 + colorOffset];
    chess::consts::bitboard knights = pieceBoard[1 + colorOffset];
    chess::consts::bitboard bishops = pieceBoard[2 + colorOffset];
    chess::consts::bitboard rooks = pieceBoard[3 + colorOffset];
    chess::consts::bitboard queens = pieceBoard[4 + colorOffset];
    chess::consts::bitboard kings = pieceBoard[5 + colorOffset];
    auto colorBoards = board.get_color_boards ();
    chess::consts::bitboard thisColorBoard = white_to_play ? colorBoards[0] : colorBoards[1];
    chess::consts::bitboard enemyColorBoard = white_to_play ? colorBoards[1] : colorBoards[0];
    chess::consts::bitboard blockerBoard = thisColorBoard | enemyColorBoard;

    chess::consts::bitboard target = (chess::consts::bitboard)1 << square;

    // Bishops, Queens
    chess::consts::bitboard diagonalSliders = bishops | queens;

    chess::consts::bitboard occupation = blockerBoard & chess::data::relevantoccupancy_masks_bishop[square];
    chess::consts::bitboard moves = chess::data::bishopMoves[square][(occupation * chess::data::magics_bishop[square]) >> (64 - chess::data::width_bishop)];
    if ((diagonalSliders & moves) > 0)
        {
            return true;
        }

    // Rooks, Queens
    chess::consts::bitboard lineSliders = rooks | queens;
    occupation = blockerBoard & chess::data::relevantoccupancy_masks_rook[square];
    moves = chess::data::rookMoves[square][(occupation * chess::data::magics_rook[square]) >> (64 - chess::data::width_rook)];
    if ((lineSliders & moves) > 0)
        {
            return true;
        }

    // Knights
    if ((knightMoves[square] & knights) > 0)
        {
            return true;
        }

    // King
    if ((kingMoves[square] & kings) > 0)
        {
            return true;
        }

    // Pawns
    if (white_to_play)
        {
            if ((((pawns & n_fileMasks[7]) >> 7) & target) > 0)
                {
                    return true;
                }
            if ((((pawns & n_fileMasks[0]) >> 9) & target) > 0)
                {
                    return true;
                }
        }
    else
        {
            if ((((pawns & n_fileMasks[0]) << 7) & target) > 0)
                {
                    return true;
                }
            if ((((pawns & n_fileMasks[7]) << 9) & target) > 0)
                {
                    return true;
                }
        }

    return false;
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

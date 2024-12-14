#ifndef MOVEGENERATOR_MOVEGENERATOR_HPP
#define MOVEGENERATOR_MOVEGENERATOR_HPP

#include "Defs.hpp"
#include "board.hpp"
#include <array>

namespace chess
{
namespace movegenerator
{
class MoveGenerator
{
  private:
    std::array<chess::consts::bitboard, 8> fileMasks;
    std::array<chess::consts::bitboard, 8> rankMasks;
    std::array<chess::consts::bitboard, 8> n_fileMasks;
    std::array<chess::consts::bitboard, 8> n_rankMasks;
    std::array<chess::consts::bitboard, 64> knightMoves;
    std::array<chess::consts::bitboard, 64> kingMoves;

    chess::board::Board board;
    std::array<chess::consts::bitboard, 12> pieceBoards;
    std::array<chess::consts::bitboard, 2> colorBoards;
    chess::consts::bitboard ghostboard;
    chess::consts::bitboard blockerBoard;
    chess::consts::bitboard n_blockerBoard;
    bool white_to_play;
    uint colorOffset;
    chess::consts::bitboard myColorBoard;
    chess::consts::bitboard n_myColorBoard;
    chess::consts::bitboard enemyColorBoard;
    chess::consts::bitboard n_enemyColorBoard;

    std::vector<chess::consts::move> persistent_pseudo_legalMoves;
    std::vector<chess::consts::move> persistent_legalMoves;

    void initMasks ();
    void initKnightMoves ();
    void initRookMoves ();
    void initKingMoves ();
    void initBishopMoves ();

    void fillPawnMoves (chess::consts::bitboard pawnBoard, std::vector<chess::consts::move> &pseudo_legalMoves);
    void fillKnightMoves (chess::consts::bitboard knightBoard, std::vector<chess::consts::move> &pseudo_legalMoves);
    void fillBishopMoves (chess::consts::bitboard bishopBoard, std::vector<chess::consts::move> &pseudo_legalMoves);
    void fillRookMoves (chess::consts::bitboard rookBoard, std::vector<chess::consts::move> &pseudo_legalMoves);
    void fillQueenMoves (chess::consts::bitboard queenBoard, std::vector<chess::consts::move> &pseudo_legalMoves);
    void fillKingMoves (chess::consts::bitboard kingBoard, std::vector<chess::consts::move> &pseudo_legalMoves);
    void fillCastlingMoves (chess::engine::Engine &engine, std::vector<chess::consts::move> &legalMoves);
    void filterIllegalMoves (chess::engine::Engine &engine, std::vector<chess::consts::move> &pseudo_legalMoves, std::vector<chess::consts::move> &legalMoves);
    void fillPawnCaptures (chess::consts::bitboard pawnBoard, std::vector<chess::consts::move> &pseudo_legalMoves);
    void fillKnightCaptures (chess::consts::bitboard knightBoard, std::vector<chess::consts::move> &pseudo_legalMoves);
    void fillBishopCaptures (chess::consts::bitboard bishopBoard, std::vector<chess::consts::move> &pseudo_legalMoves);
    void fillRookCaptures (chess::consts::bitboard rookBoard, std::vector<chess::consts::move> &pseudo_legalMoves);
    void fillQueenCaptures (chess::consts::bitboard queenBoard, std::vector<chess::consts::move> &pseudo_legalMoves);
    void fillKingCaptures (chess::consts::bitboard kingBoard, std::vector<chess::consts::move> &pseudo_legalMoves);
    void fillPawnAttacks (chess::consts::bitboard pawnBoard, chess::consts::bitboard &attacks);
    void fillKnightAttacks (chess::consts::bitboard knightBoard, chess::consts::bitboard &attacks);
    void fillBishopAttacks (chess::consts::bitboard bishopBoard, chess::consts::bitboard &attacks);
    void fillRookAttacks (chess::consts::bitboard rookBoard, chess::consts::bitboard &attacks);
    void fillQueenAttacks (chess::consts::bitboard queenBoard, chess::consts::bitboard &attacks);
    void fillKingAttacks (chess::consts::bitboard kingBoard, chess::consts::bitboard &attacks);

  public:
    MoveGenerator ();
    std::vector<consts::move> &GetLegalMoves (chess::engine::Engine &engine);
    chess::consts::bitboard GetAttacks (chess::engine::Engine &engine, const bool &white_to_play);
    chess::consts::bitboard GetAttacks (chess::engine::Engine &engine, const chess::consts::Piece piece, const int square);
    std::vector<consts::move> &GetLegalCaptures (chess::engine::Engine &engine);
    bool IsSquareAttacked (chess::engine::Engine &engine, const bool &white_to_play, const chess::consts::Square &square);
};
}
}

#endif

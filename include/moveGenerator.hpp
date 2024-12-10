#ifndef MOVEGENERATOR_MOVEGENERATOR_HPP
#define MOVEGENERATOR_MOVEGENERATOR_HPP

#include "Defs.hpp"
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

    void initMasks ();
    void initKnightMoves ();
    void initRookMoves ();
    void initKingMoves ();
    void initBishopMoves ();

  public:
    MoveGenerator ();
    std::vector<consts::move> GetLegalMoves (chess::engine::Engine &engine);
    chess::consts::bitboard GetAttacks (chess::engine::Engine &engine, const bool &white_to_play);
    std::vector<consts::move> GetLegalCaptures (chess::engine::Engine &engine);
    bool IsSquareAttacked (chess::engine::Engine &engine, const bool &white_to_play, const chess::consts::Square &square);
};
}
}

#endif

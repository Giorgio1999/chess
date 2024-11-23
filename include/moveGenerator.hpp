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

    void initMasks ();
    void initKnightMoves ();

  public:
    MoveGenerator ();
    std::vector<consts::move> GetLegalMoves (chess::engine::Engine &engine);
};
}
}

#endif

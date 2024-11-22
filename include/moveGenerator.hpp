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

    void initMasks ();

  public:
    MoveGenerator ();
    std::vector<consts::move> GetLegalMoves (chess::engine::Engine &engine);
};
}
}

#endif

#ifndef BOARD_BOARD_HPP
#define BOARD_BOARD_HPP

#include <array>
#include <string>
#include "Defs.hpp"

namespace chess
{
class Board
{
  private:
    std::array<bitboard, 12> piece_boards;

  public:
    std::string ShowBoard ();
};
}

#endif

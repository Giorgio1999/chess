#ifndef BOARD_BOARD_HPP
#define BOARD_BOARD_HPP

#include <array>
#include <string>
#include "Defs.hpp"

struct castle_rights
{
    bool K = true;
    bool Q = true;
    bool k = true;
    bool q = true;
};

namespace chess
{
namespace board
{
class Board
{
  private:
    std::array<consts::bitboard, 12> piece_boards;
    consts::bitboard ghost_board = 0;
    consts::flag board_flag = 0b10111101;

  public:
    Board ();
    std::string ShowBoard ();
    bool white_to_play ();
    bool enpassantable ();
    castle_rights castling ();
    void flip_white_to_play ();
    void flip_enpassantable ();
    void flip_castling (chess::consts::castling_rights_name _castling);
    void flip_ghost_board (const int square);
};
std::string square2string (const int square);
}
}

#endif

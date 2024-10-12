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

enum castling_rights_name
{
    K,
    Q,
    k,
    q
};

namespace chess
{
class Board
{
  private:
    std::array<consts::bitboard, 12> piece_boards;
    consts::bitboard ghost_board = 0;
    consts::flag board_flag = consts::BOARD_FLAG_MAX;

  public:
    Board ();
    std::string ShowBoard ();
    bool white_to_play ();
    bool enpassantable ();
    castle_rights castling ();
    void flip_white_to_play ();
    void flip_enpassantable ();
    void flip_castling (castling_rights_name _castling);
};
}

#endif

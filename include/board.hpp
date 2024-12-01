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
    std::array<consts::bitboard, 2> color_boards;
    consts::bitboard ghost_board = 0;
    consts::flag board_flag = 0;

  public:
    Board ();
    void init ();
    std::string ShowBoard ();
    bool white_to_play ();
    bool enpassantable ();
    castle_rights castling ();
    void flip_white_to_play ();
    void set_enpassantable ();
    void clear_enpassantable ();
    void flip_castling (chess::consts::castling_rights_name _castling);
    void clear_castling (chess::consts::castling_rights_name _castling);
    void flip_ghost_board (const int square);
    void set_piece (const int square, const consts::Piece _piece);
    void makeMove (const consts::move move);
    void sanitize (consts::move &move);
    void init_color_boards ();
    std::array<consts::bitboard, 12>
    get_piece_boards ()
    {
        return piece_boards;
    }
    std::array<consts::bitboard, 2>
    get_color_boards ()
    {
        return color_boards;
    }
    chess::consts::bitboard
    get_ghost_board ()
    {
        return ghost_board;
    }
};
std::string square2string (const int square);
int string2square (const std::string string);
}
}

#endif

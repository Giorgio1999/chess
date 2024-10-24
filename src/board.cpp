#include "board.hpp"
#include "bitboard.hpp"
#include "flags.hpp"
#include <string>
#include <array>

namespace chess
{
namespace board
{
Board::Board ()
{
    for (int i = 0; i < 12; i++)
        {
            piece_boards[i] = 0;
        }
}

bool
Board::white_to_play ()
{
    return flags::is_wtp (board_flag);
}

bool
Board::enpassantable ()
{
    return flags::is_enp (board_flag);
}

castle_rights
Board::castling ()
{
    return { flags::is_K (board_flag), flags::is_Q (board_flag), flags::is_k (board_flag), flags::is_q (board_flag) };
}
void
Board::flip_white_to_play ()
{
    flags::flip_wtp (board_flag);
}

void
Board::flip_enpassantable ()
{
    flags::flip_enp (board_flag);
}

void
Board::flip_castling (chess::consts::castling_rights_name _castling)
{
    switch (_castling)
        {
        case chess::consts::castling_rights_name::CASTLE_K:
            flags::flip_K (board_flag);
            break;
        case chess::consts::castling_rights_name::CASTLE_Q:
            flags::flip_Q (board_flag);
            break;
        case chess::consts::castling_rights_name::CASTLE_k:
            flags::flip_k (board_flag);
            break;
        case chess::consts::castling_rights_name::CASTLE_q:
            flags::flip_q (board_flag);
            break;
        }
}

std::string
Board::ShowBoard ()
{
    std::array<std::string, 64> field_occupations;
    for (int i = 0; i < 12; i++)
        {
            consts::bitboard piece_board = piece_boards[i];
            while (piece_board > 0)
                {
                    int lsb = chess::bitboard_helper::pop_lsb (piece_board);
                    field_occupations[lsb] = consts::pieces[i];
                }
        }
    consts::bitboard ghost_board_tmp = ghost_board;
    int ghost_position = -1;
    while (ghost_board_tmp > 0)
        {
            ghost_position = chess::bitboard_helper::pop_lsb (ghost_board_tmp);
            field_occupations[ghost_position] = white_to_play () ? consts::pieces[12] : consts::pieces[13];
        }
    std::string board_visual = "";
    for (int i = 0; i < 8; i++)
        {
            for (int j = 0; j < 8; j++)
                {
                    std::string piece = field_occupations[i * 8 + j];
                    if (piece == "")
                        {
                            piece = "-";
                        }
                    board_visual += piece;
                }
            board_visual += "\n";
        }
    board_visual += "Flags:";
    board_visual += white_to_play () ? "w" : "b";
    board_visual += "";
    board_visual += enpassantable () ? square2string (ghost_position) : "-";
    board_visual += "";
    board_visual += castling ().K ? "K" : "-";
    board_visual += castling ().Q ? "Q" : "-";
    board_visual += castling ().k ? "k" : "-";
    board_visual += castling ().q ? "q" : "-";
    board_visual += "\n";
    return board_visual;
}

void
Board::flip_ghost_board (const int square)
{
    bitboard_helper::flip_bit (ghost_board, square);
}

std::string
square2string (const int square)
{
    std::string res = "";
    res += consts::squares[square * 2];
    res += consts::squares[square * 2 + 1];
    return res;
}
}
}

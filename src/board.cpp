#include "board.hpp"
#include "Defs.hpp"
#include "bitboard.hpp"
#include "flags.hpp"
#include "moves.hpp"
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

void
Board::init ()
{

    for (int i = 0; i < 12; i++)
        {
            piece_boards[i] = 0;
        }
    ghost_board = 0;
    board_flag = 0;
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
Board::set_enpassantable ()
{
    flags::set_enp (board_flag);
}

void
Board::clear_enpassantable ()
{
    flags::clear_enp (board_flag);
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

void
Board::clear_castling (chess::consts::castling_rights_name _castling)
{
    switch (_castling)
        {
        case chess::consts::castling_rights_name::CASTLE_K:
            flags::clear_K (board_flag);
            break;
        case chess::consts::castling_rights_name::CASTLE_Q:
            flags::clear_Q (board_flag);
            break;
        case chess::consts::castling_rights_name::CASTLE_k:
            flags::clear_k (board_flag);
            break;
        case chess::consts::castling_rights_name::CASTLE_q:
            flags::clear_q (board_flag);
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
            field_occupations[ghost_position] = white_to_play () ? consts::pieces[13] : consts::pieces[12];
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

int
string2square (const std::string string)
{
    for (int i = 0; i < 64; i++)
        {
            if (consts::squares[i * 2] == string[0] && consts::squares[i * 2 + 1] == string[1])
                {
                    return i;
                }
        }
    return -1;
}

void
Board::set_piece (const int square, const consts::Piece _piece)
{
    bitboard_helper::flip_bit (piece_boards[_piece], square);
}

void
Board::makeMove (const consts::move move)
{
    int startsquare = moves::getStartSquare (move);
    consts::bitboard from = (consts::bitboard)1 << startsquare;
    consts::Piece movepiece = consts::Piece::empty;
    for (int i = 0; i < 12; i++)
        {
            consts::bitboard tmp_board = piece_boards[i] & from;
            if (tmp_board > 0)
                {
                    movepiece = (consts::Piece)i;
                    break;
                }
        }
    int endsquare = moves::getEndSquare (move);
    consts::bitboard to = (consts::bitboard)1 << endsquare;
    consts::Piece takepiece = consts::Piece::empty;
    for (int i = 0; i < 12; i++)
        {
            consts::bitboard tmp_board = piece_boards[i] & to;
            if (tmp_board > 0)
                {
                    takepiece = (consts::Piece)i;
                    break;
                }
        }
    piece_boards[movepiece] ^= from;
    piece_boards[movepiece] ^= to;
    if (takepiece != consts::Piece::empty)
        {
            piece_boards[takepiece] ^= to;
        }
    ghost_board = 0;
    clear_enpassantable ();
    if (movepiece == consts::Piece::P || movepiece == consts::Piece::p)
        {
            if (std::abs (startsquare - endsquare) == 16)
                {
                    set_enpassantable ();
                    if (white_to_play ())
                        {
                            ghost_board ^= to << 8;
                        }
                    else
                        {
                            ghost_board ^= to >> 8;
                        }
                }
        }
    if (movepiece == consts::Piece::k)
        {
            clear_castling (consts::castling_rights_name::CASTLE_k);
            clear_castling (consts::castling_rights_name::CASTLE_q);
            if (startsquare == consts::Square::E8)
                {
                    if (endsquare == consts::Square::G8)
                        {
                            piece_boards[consts::Piece::r] ^= (consts::bitboard)1 << consts::Square::H8;
                            piece_boards[consts::Piece::r] ^= (consts::bitboard)1 << consts::Square::F8;
                        }
                    if (endsquare == consts::Square::C8)
                        {
                            piece_boards[consts::Piece::r] ^= (consts::bitboard)1 << consts::Square::A8;
                            piece_boards[consts::Piece::r] ^= (consts::bitboard)1 << consts::Square::D8;
                        }
                }
        }
    if (movepiece == consts::Piece::K)
        {
            clear_castling (consts::castling_rights_name::CASTLE_K);
            clear_castling (consts::castling_rights_name::CASTLE_Q);
            if (startsquare == consts::Square::E1)
                {
                    if (endsquare == consts::Square::G1)
                        {
                            piece_boards[consts::Piece::R] ^= (consts::bitboard)1 << consts::Square::H1;
                            piece_boards[consts::Piece::R] ^= (consts::bitboard)1 << consts::Square::F1;
                        }
                    if (endsquare == consts::Square::C1)
                        {
                            piece_boards[consts::Piece::R] ^= (consts::bitboard)1 << consts::Square::A1;
                            piece_boards[consts::Piece::R] ^= (consts::bitboard)1 << consts::Square::D1;
                        }
                }
        }
    if (startsquare == consts::Square::H1 || endsquare == consts::Square::H1)
        {
            clear_castling (consts::castling_rights_name::CASTLE_K);
        }
    if (startsquare == consts::Square::A1 || endsquare == consts::Square::A1)
        {
            clear_castling (consts::castling_rights_name::CASTLE_Q);
        }
    if (startsquare == consts::Square::H8 || endsquare == consts::Square::H8)
        {
            clear_castling (consts::castling_rights_name::CASTLE_k);
        }
    if (startsquare == consts::Square::A8 || endsquare == consts::Square::A8)
        {
            clear_castling (consts::castling_rights_name::CASTLE_q);
        }
    flip_white_to_play ();
}
}
}

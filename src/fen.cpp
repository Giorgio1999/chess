#include "fen.hpp"
#include "board.hpp"
#include <string>
#include <regex>

namespace chess
{
namespace fen
{
void
parse (const std::string &fen, board::Board &board)
{
    board.init ();
    // regex patter to find words seperated by whitespaces
    std::regex re ("\\S+");
    std::sregex_iterator it (fen.begin (), fen.end (), re);
    std::sregex_iterator it_end;
    std::string position = it->str ();
    CERR << position << std::endl;
    ++it;
    std::string side = it->str ();
    CERR << side << std::endl;
    ++it;
    std::string castling = it->str ();
    CERR << castling << std::endl;
    ++it;
    std::string en_passant = it->str ();
    CERR << en_passant << std::endl;
    ++it;
    std::string half_move = it->str ();
    CERR << half_move << std::endl;
    ++it;
    std::string full_move = it->str ();
    CERR << full_move << std::endl;
    ++it;

    // position parsing
    std::regex re2 ("([pnbrqkPNBRQK1-8])+");
    std::sregex_iterator it2 (position.begin (), position.end (), re2);
    std::sregex_iterator it2_end;
    int square = 0;
    for (; it2 != it2_end; ++it2)
        {
            std::string line = it2->str ();
            for (char piece : line)
                {
                    auto _pos = consts::pieces.find (piece);
                    if (_pos == std::string::npos)
                        {
                            square += piece - '0';
                        }
                    else
                        {
                            consts::Piece _piece = (consts::Piece)_pos;
                            board.set_piece (square, _piece);
                            square++;
                        }
                }
        }

    // side parsing
    if (side == "w")
        {
            // starts of as b
            board.flip_white_to_play ();
        }

    // castling parsing
    if (castling != "-")
        {
            if (castling.find ('K') != std::string::npos)
                {
                    board.flip_castling (consts::castling_rights_name::CASTLE_K);
                }
            if (castling.find ('Q') != std::string::npos)
                {
                    board.flip_castling (consts::castling_rights_name::CASTLE_Q);
                }
            if (castling.find ('k') != std::string::npos)
                {
                    board.flip_castling (consts::castling_rights_name::CASTLE_k);
                }
            if (castling.find ('q') != std::string::npos)
                {
                    board.flip_castling (consts::castling_rights_name::CASTLE_q);
                }
        }

    // en passant parsing
    if (en_passant != "-")
        {
            CERR << en_passant << std::endl;
            board.set_enpassantable ();
            board.flip_ghost_board (board::string2square (en_passant));
        }
    board.init_color_boards ();
}
std::string
generate (const board::Board &board)
{
    return "";
}
}
}

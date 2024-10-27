#ifndef FEN_FEN_HPP
#define FEN_FEN_HPP
#include <string>
namespace chess
{
namespace board
{
class Board;
}
namespace fen
{

void parse (const std::string &fen, board::Board &board);
std::string generate (const board::Board &board);
}
}

#endif

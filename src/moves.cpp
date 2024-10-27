#include <string>
#include "Defs.hpp"
#include "moves.hpp"
#include "board.hpp"

namespace chess
{
namespace moves
{
int
getStartSquare (consts::move move)
{
    return (move >> 8) & 0b11111111;
}

int
getEndSquare (consts::move move)
{
    return move & 0b11111111;
}

consts::move
move_ (int startsquare, int endsquare)
{
    return (startsquare << 8) | endsquare;
}

consts::move
string2move (std::string movestring)
{
    std::string startsquare = movestring.substr (0, 2);
    std::string endsquare = movestring.substr (2, 4);
    consts::move move = move_ (board::string2square (startsquare), board::string2square (endsquare));
    return move;
}
std::string
move2string (consts::move move)
{
    std::string movestring = board::square2string (getStartSquare (move)) + board::square2string (getEndSquare (move));
    return movestring;
}
}
}

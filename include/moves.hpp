#ifndef MOVES_MOVES_HPP
#define MOVES_MOVES_HPP
#include <string>
#include "Defs.hpp"

namespace chess
{
namespace moves
{
int getStartSquare (consts::move);
int getEndSquare (consts::move);
consts::move move_ (int startsquare, int endsquare);
consts::move string2move (std::string);
std::string move2string (consts::move);

}
}

#endif

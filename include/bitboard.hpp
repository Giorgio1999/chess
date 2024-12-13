#ifndef BITBOARD_BITBOARD_HPP
#define BITBOARD_BITBOARD_HPP
#include "Defs.hpp"

namespace chess
{
namespace bitboard_helper
{
/*inline int pop_lsb (consts::bitboard &b);*/
inline int
pop_lsb (consts::bitboard &b)
{
    int res = __builtin_ffsll (b) - 1;
    if (res > -1)
        {
            b ^= (consts::bitboard)1 << res;
        }
    return res;
}

inline int
count (const consts::bitboard &b)
{
    return __builtin_popcount (b);
}

void flip_bit (consts::bitboard &b, const int square);
std::string visualize_bitboard (chess::consts::bitboard b);
}
}

#endif

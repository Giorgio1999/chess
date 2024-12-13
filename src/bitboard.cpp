#include "bitboard.hpp"
#include "Defs.hpp"
#include <cstdint>

namespace chess
{
namespace bitboard_helper
{
/*inline int*/
/*pop_lsb (consts::bitboard &b)*/
/*{*/
/*    int res = __builtin_ffsll (b) - 1;*/
/*    if (res > -1)*/
/*        {*/
/*            b ^= (consts::bitboard)1 << res;*/
/*        }*/
/*    return res;*/
/*}*/

void
flip_bit (consts::bitboard &b, const int square)
{
    b ^= (consts::bitboard)1 << square;
}

std::string
visualize_bitboard (chess::consts::bitboard b)
{
    std::array<uint, 64> occupations;
    for (uint i = 0; i < 64; i++)
        {
            occupations[i] = 0;
        }
    while (b > 0)
        {
            uint i = pop_lsb (b);
            occupations[i] = 1;
        }
    std::string res;
    for (uint i = 0; i < 8; i++)
        {
            for (uint j = 0; j < 8; j++)
                {
                    res += occupations[i * 8 + j] == 1 ? "o" : "-";
                }
            res += "\n";
        }
    return res;
}

/*int*/
/*count (chess::consts::bitboard b)*/
/*{*/
/*    int res = 0;*/
/*    while (b > 0)*/
/*        {*/
/*            res++;*/
/*            int dum = pop_lsb (b);*/
/*        }*/
/*    return res;*/
/*}*/
}
}

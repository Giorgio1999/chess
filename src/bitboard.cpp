#include "bitboard.hpp"
#include "Defs.hpp"
#include <cstdint>

namespace chess
{
namespace bitboard_helper
{
int
pop_lsb (bitboard &b)
{
    int res = __builtin_ffsll (b) - 1;
    if (res > -1)
        {
            b ^= (bitboard)1 << res;
        }
    return res;
}
}
}
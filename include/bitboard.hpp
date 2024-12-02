#ifndef BITBOARD_BITBOARD_HPP
#define BITBOARD_BITBOARD_HPP
#include "Defs.hpp"

namespace chess
{
namespace bitboard_helper
{
int pop_lsb (consts::bitboard &b);
void flip_bit (consts::bitboard &b, const int square);
std::string visualize_bitboard (chess::consts::bitboard b);
int count (consts::bitboard b);
}
}

#endif

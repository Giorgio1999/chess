#ifndef HASH_HPP_HPP
#define HASH_HPP_HPP
#include <array>
#include "Defs.hpp"
#include "board.hpp"

namespace chess
{
namespace hash
{
struct table
{
    std::array<std::array<chess::consts::hash, 64>, 12> pieces;
    chess::consts::hash white_to_play;
};
extern table hash_table;

void init_hash_table ();
chess::consts::hash get_hash (chess::board::Board &board);
}
}

#endif

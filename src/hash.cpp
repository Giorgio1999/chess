#include "hash.hpp"
#include <random>
#include <cmath>
#include "board.hpp"
#include "bitboard.hpp"

namespace chess
{
namespace hash
{
chess::hash::table hash_table;

void
init_hash_table ()
{

    std::random_device rd;
    std::mt19937_64 e2 (rd ());
    std::uniform_int_distribution<chess::consts::hash> dist (0, std::llround (std::pow (2, 64) - 1));
    for (int piece = 0; piece < 12; piece++)
        {
            for (int square = 0; square < 64; square++)
                {
                    hash_table.pieces[piece][square] = dist (e2);
                }
        }
    hash_table.white_to_play = dist (e2);
}

chess::consts::hash
get_hash (chess::board::Board &board)
{
    std::array<chess::consts::bitboard, 12> pieceBoards = board.get_piece_boards ();
    chess::consts::hash hash = (chess::consts::hash)0;
    for (int piece = 0; piece < 12; piece++)
        {
            while (pieceBoards[piece] > 0)
                {
                    int square = chess::bitboard_helper::pop_lsb (pieceBoards[piece]);
                    hash ^= hash_table.pieces[piece][square];
                }
        }
    if (board.white_to_play ())
        {
            hash ^= hash_table.white_to_play;
        }
    return hash;
}
}
}

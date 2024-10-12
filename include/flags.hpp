#ifndef FLAGS_FLAGS_HPP
#define FLAGS_FLAGS_HPP
#include <Defs.hpp>

namespace chess
{
namespace flags
{
int pop_lsb (consts::flag &flag);
bool check_board (const consts::flag &_board_flag, const consts::flag &_check_flag);
void flip_board (consts::flag &_board_flag, const consts::flag &_flip_flag);
bool is_wtp (const consts::flag &_board_flag);
bool is_enp (const consts::flag &_board_flag);
bool is_Q (const consts::flag &_board_flag);
bool is_K (const consts::flag &_board_flag);
bool is_q (const consts::flag &_board_flag);
bool is_k (const consts::flag &_board_flag);
void flip_wtp (consts::flag &_board_flag);
void flip_enp (consts::flag &_board_flag);
void flip_Q (consts::flag &_board_flag);
void flip_K (consts::flag &_board_flag);
void flip_q (consts::flag &_board_flag);
void flip_k (consts::flag &_board_flag);
}
}

#endif

#include "Defs.hpp"
#include "flags.hpp"
#include <cassert>
#include "bitboard.hpp"

namespace chess
{
namespace flags
{
int
pop_lsb (consts::flag &flag)
{
    int res = __builtin_ffs (flag) - 1;
    if (res > -1)
        {
            flag ^= (consts::flag)1 << res;
        }
    return res;
}
bool
check_board (const consts::flag &_board_flag, const consts::flag &_check_flag)
{
#ifdef DEBUG
    assert (_board_flag & consts::BOARD > 0);
#endif
    return (_board_flag & _check_flag) > 0;
}
void
flip_board (consts::flag &_board_flag, const consts::flag &_flip_flag)
{
#ifdef DEBUG
    assert (_board_flag & consts::BOARD > 0);
#endif
    _board_flag ^= _flip_flag;
}
bool
is_wtp (const consts::flag &_board_flag)
{
    return check_board (_board_flag, consts::WTP_FLAG);
}
bool
is_enp (const consts::flag &_board_flag)
{
    return check_board (_board_flag, consts::ENP_FLAG);
}
bool
is_Q (const consts::flag &_board_flag)
{
    return _board_flag & consts::Q_FLAG;
}
bool
is_K (const consts::flag &_board_flag)
{
    return _board_flag & consts::K_FLAG;
}
bool
is_q (const consts::flag &_board_flag)
{
    return _board_flag & consts::q_FLAG;
}
bool
is_k (const consts::flag &_board_flag)
{
    return _board_flag & consts::k_FLAG;
}
void
flip_wtp (consts::flag &_board_flag)
{
    flip_board (_board_flag, consts::WTP_FLAG);
}
void
flip_enp (consts::flag &_board_flag)
{
    flip_board (_board_flag, consts::ENP_FLAG);
}
void
flip_Q (consts::flag &_board_flag)
{
    flip_board (_board_flag, consts::Q_FLAG);
}

void
flip_K (consts::flag &_board_flag)
{
    flip_board (_board_flag, consts::K_FLAG);
}
void
flip_q (consts::flag &_board_flag)
{
    flip_board (_board_flag, consts::q_FLAG);
}
void
flip_k (consts::flag &_board_flag)
{
    flip_board (_board_flag, consts::k_FLAG);
}
}
}

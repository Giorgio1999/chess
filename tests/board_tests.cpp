#include <gtest/gtest.h>
#include "board.hpp"
#include "Defs.hpp"

TEST (board_tests, board_test_1)
{
    chess::Board b;
    b.flip_enpassantable ();
    std::cout << b.ShowBoard () << std::endl;
    EXPECT_EQ (b.ShowBoard (), "rnbqkbnr/pppppppp/8/8/8/8/PPPPPPPP/RNBQKBNR w KQkq - 0 1");
}

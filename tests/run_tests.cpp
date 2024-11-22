#include <gtest/gtest.h>
#include "Defs.hpp"
#include "engine_handler.hpp"

int
main (int argc, char **argv)
{
    ::testing::InitGoogleTest (&argc, argv);
    return RUN_ALL_TESTS ();
}

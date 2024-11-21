#include <chrono>
#include <gtest/gtest.h>
#include "engine.hpp"
#include "chessConfig.h"
#include "moves.hpp"

TEST (engine_tests, engine_undomove)
{
    chess::engine::Engine engine ("test_engine", "test_author");
    std::string dum = engine.Position (chess::consts::startpos);
    std::string prevboard = engine.ShowBoard ();
    engine.MakeMove (chess::moves::string2move ("e1e2"));
    engine.UndoMove ();
    std::string nextboard = engine.ShowBoard ();
    EXPECT_EQ (prevboard, nextboard);

    dum = engine.Position (chess::consts::startpos);
    prevboard = engine.ShowBoard ();
    for (uint i = 0; i < 100; i++)
        {
            engine.MakeMove (123);
        }
    for (uint i = 0; i < 100; i++)
        {
            engine.UndoMove ();
        }
    nextboard = engine.ShowBoard ();
    EXPECT_EQ (prevboard, nextboard);
}

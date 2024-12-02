#include "chess.hpp"
#include <iostream>
#include <chrono>
#include <thread>

std::string
Search (chess::engine::Engine &engine)
{
    bool whiteToPlay = engine.GetBoard ().white_to_play ();
    std::vector<chess::consts::move> legalMoves = engine.GetLegalMoves ();
    return "bestmove " + chess::moves::move2string (legalMoves[0]);
}

int
main ()
{
    chess::engine::Engine engine ("example_engine", "example_author");
    engine.SetVersion_Major (1);
    engine.SetVersion_Minor (0);
    engine.SetVersion_Patch (0);
    engine.SetSearch (Search);
    chess::engine::Handler handler (engine, std::cin, std::cout);
    return 0;
}

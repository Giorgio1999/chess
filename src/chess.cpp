#include "chess.hpp"
#include "engine.hpp"
#include <string>
#include "chessConfig.h"
#include "Defs.hpp"

namespace chess
{
std::string
Welcome ()
{
    std::string message = "chess library version " + std::to_string (chess_VERSION_MAJOR) + "." + std::to_string (chess_VERSION_MINOR) + "." + std::to_string (chess_VERSION_PATCH) + " configuration " + CONFIGURATION;
    CERR << "Active" << std::endl;
    return message;
}

std::string
Search ()
{
    engine::Engine *engine = new engine::Engine ("example_engine", "example_author");
    return engine->Search ();
}
}

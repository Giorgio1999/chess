#include "engine.hpp"
#include "Defs.hpp"
#include "chessConfig.h"
#include <string>
#include <mutex>

std::mutex stop_mutex;

namespace chess
{
namespace engine
{
std::string
Engine::Introduce ()
{
    std::string out = "id name " + name + " " + std::to_string (version_major) + "." + std::to_string (version_minor) + "." + std::to_string (version_patch);
    out += " chess " + std::to_string (chess_VERSION_MAJOR) + "." + std::to_string (chess_VERSION_MINOR) + "." + std::to_string (chess_VERSION_PATCH) + " " + consts::CONFIGURATION + "\n";
    out += "id author " + author;
    return out;
}
void
Engine::Stop ()
{
    std::lock_guard<std::mutex> lock (stop_mutex);
    CERR << "Engine stopped" << std::endl;
    stop = true;
}
void
Engine::UnStop ()
{
    std::lock_guard<std::mutex> lock (stop_mutex);
    CERR << "Engine un-stopped" << std::endl;
    stop = false;
}
}
}

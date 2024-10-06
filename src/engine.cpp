#include "engine.hpp"
#include <string>

namespace chess
{
namespace engine
{
std::string
Engine::Introduce ()
{
    return name + " " + std::to_string (version_major) + "." + std::to_string (version_minor) + "." + std::to_string (version_patch) + "\n" + author;
}
}
}

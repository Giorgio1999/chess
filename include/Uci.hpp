#ifndef UCI_UCI_HPP
#define UCI_UCI_HPP
#include "engine.hpp"
#include "Defs.hpp"
#include <string>
#include <functional>
#include <unordered_map>
#include <stdexcept>

namespace chess
{
namespace interface
{
struct Uci
{
  private:
    std::unordered_map<std::string, consts::Command> commands;

  public:
    Uci ();
    consts::Command operator[] (std::string command);
};
}
}

std::string uci (chess::engine::Engine &engine, std::string _command);
std::string quit (chess::engine::Engine &engine, std::string _command);
std::string stop (chess::engine::Engine &engine, std::string _command);
std::string isready (chess::engine::Engine &engine, std::string _command);
std::string go (chess::engine::Engine &engine, std::string _command);

void Split (std::string &command, std::string &args);

#endif

#ifndef ENGINE_HANDLER_ENGINE_HANDLER_HPP
#define ENGINE_HANDLER_ENGINE_HANDLER_HPP
#include "engine.hpp"
#include "Defs.hpp"
#include "Uci.hpp"
#include <queue>

namespace chess
{
namespace engine
{
class Handler
{
  private:
    chess ::engine::Engine engine;
    std::istream &input;
    std::ostream &output;
    void MainLoop ();

  public:
    Handler (chess ::engine::Engine &_engine, std::istream &_input, std::ostream &_output);
    chess::engine::Engine &
    GetEngine ()
    {
        return engine;
    }

    void
    SetEngine (chess ::engine::Engine &_engine)
    {
        engine = _engine;
    }
};
}
}
struct Commands
{
    std::queue<std::string> command_queue;

    void
    push (std::string _command)
    {
        if (_command == "quit")
            {
                throw 0;
            }
        else if (_command == "stop")
            {
                throw 1;
            }
        else
            {
                command_queue.push (_command);
            }
    }
    void
    pop ()
    {
        command_queue.pop ();
    }
    std::string
    front ()
    {
        return command_queue.front ();
    }
    size_t
    size ()
    {
        return command_queue.size ();
    }
    bool
    empty ()
    {
        return command_queue.empty ();
    }
};
class BackGroundWorker
{

  public:
    BackGroundWorker (Commands &_commands, chess ::engine::Engine &_engine, chess::interface::Uci &_uci);
};
#endif

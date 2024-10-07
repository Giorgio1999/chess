#include "engine_handler.hpp"
#include "Uci.hpp"
#include "Defs.hpp"
#include <istream>
#include <string>
#include <thread>
#include <mutex>
#include <condition_variable>

std::mutex commands_mutex;
std::condition_variable commands_cv;
bool done = false;

namespace chess
{
namespace engine
{

Handler::Handler (chess ::engine::Engine &_engine, std::istream &_input, std::ostream &_output) : engine (_engine), input (_input), output (_output) { MainLoop (); }
void
Handler::MainLoop ()
{
    Commands commands;
    chess::interface::Uci uci;
    std::thread t = std::thread ([this, &commands, &uci] { BackGroundWorker worker (commands, engine, uci); });
    std::string line;
    while (std::getline (input, line))
        {
            std::lock_guard<std::mutex> lock (commands_mutex);
            try
                {
                    commands.push (line);
                }
            catch (int e)
                {
                    if (e == 0)
                        {
                            break;
                        }
                    if (e == 1)
                        {
                            CERR << "engine_handler: requested stop" << std::endl;
                            engine.Stop ();
                        }
                }
            commands_cv.notify_one (); // notify that there is a new command
        }
    // signal that there is no more commands
    {
        std::lock_guard<std::mutex> lock (commands_mutex);
        done = true;
        commands_cv.notify_one (); // wakes the worker
    }
    t.join ();
}
}
}

BackGroundWorker::BackGroundWorker (Commands &_commands, chess ::engine::Engine &_engine, chess::interface::Uci &_uci)
{
    while (true)
        {
            std::unique_lock<std::mutex> lock (commands_mutex);
            commands_cv.wait (lock, [&] { return done || !_commands.empty (); }); // wait for command
            if (done && _commands.size () == 0)
                {
                    break;
                }
            if (!_commands.empty ())
                {
                    _engine.UnStop ();
                    std::string command = _commands.front ();
                    _commands.pop ();
                    lock.unlock (); // release lock so that the thread can use it
                    CERR << "Command: " << command << std::endl;
                    try
                        {
                            std::cout << _uci[command](_engine, command) << std::endl;
                        }
                    catch (std::runtime_error &e)
                        {
                            CERR << e.what () << std::endl;
                        }
                    catch (int e)
                        {
                            CERR << "quit" << std::endl;
                            CERR << "Engine quit" << std::endl;
                            break;
                        }
                }
        }
}

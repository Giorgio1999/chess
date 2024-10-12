#include "Uci.hpp"
#include "engine.hpp"
#include "Defs.hpp"
#include <string>
#include <iostream>
#include <regex>

std::string
uci (chess::engine::Engine &engine, std::string _command)
{
    std::string args;
    std::string command;
    Split (_command, args);

    if (args != "")
        {
            CERR << "Unknown args: " << args << std::endl;
        }
    engine.UnStop ();
    engine.SetReady (true);
    return engine.Introduce () + "\nuciok";
}

std::string
quit (chess::engine::Engine &engine, std::string _command)
{
    std::string args;
    std::string command;
    Split (_command, args);

    if (args != "")
        {
            CERR << "Unknown args: " << args << std::endl;
        }
    engine.Stop ();
    throw 0;
    return "";
}

std::string
stop (chess::engine::Engine &engine, std::string _command)
{
    std::string args;
    std::string command;
    Split (_command, args);

    if (args != "")
        {
            CERR << "Unknown args: " << args << std::endl;
        }
    engine.Stop ();
    CERR << "Engine stopped" << std::endl;
    CERR << "Engine: " << engine.IsStop () << std::endl;
    return "";
}

std::string
isready (chess::engine::Engine &engine, std::string _command)
{
    std::string args;
    std::string command;
    Split (_command, args);

    if (args != "")
        {
            CERR << "Unknown args: " << args << std::endl;
        }
    if (engine.IsReady ())
        {
            return "readyok";
        }
    else
        {
            return "";
        }
}

std::string
go (chess::engine::Engine &engine, std::string _command)
{

    std::string args;
    std::string command;
    Split (_command, args);

    if (args != "")
        {
            CERR << "Unknown args: " << args << std::endl;
        }
    return engine.Search ();
}

void
Split (std::string &command, std::string &args)
{

    std::regex re ("\\S+");
    std::sregex_iterator it (command.begin (), command.end (), re);
    command = it->str ();
    args = "";
    while (++it != std::sregex_iterator ())
        {
            args += it->str ();
            args += " ";
        }
}

namespace chess
{
namespace interface
{
Uci::Uci ()
{
    commands["uci"] = uci;
    commands["quit"] = quit;
    // commands["stop"] = stop;
    commands["isready"] = isready;
    commands["go"] = go;
}
consts::Command
Uci::operator[] (std::string _command)
{
    // Regex to find words separated by whitespaces
    std::regex re ("\\S+");
    std::sregex_iterator it (_command.begin (), _command.end (), re);
    CERR << it->str () << std::endl;
    std::string command = it->str ();

    if (commands.find (it->str ()) == commands.end ())
        {
            throw std::runtime_error ("Unknown command: " + command);
        }
    return commands[command];
}

}
}

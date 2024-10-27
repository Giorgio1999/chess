#include "Uci.hpp"
#include "engine.hpp"
#include "Defs.hpp"
#include "moves.hpp"
#include <string>
#include <iostream>
#include <regex>
#include <vector>

std::string
uci (chess::engine::Engine &engine, std::string _command)
{
    std::vector<std::string> args;
    std::string command;
    Split (_command, args);

    if (!args.empty ())
        {
            CERR << "Unknown args: " << args[0] << std::endl;
        }

    engine.UnStop ();
    engine.SetReady (true);
    return engine.Introduce () + "\nuciok";
}

std::string
quit (chess::engine::Engine &engine, std::string _command)
{
    std::vector<std::string> args;
    std::string command;
    Split (_command, args);

    if (!args.empty ())
        {
            CERR << "Unknown args: " << args[0] << std::endl;
        }

    engine.Stop ();
    throw 0;
    return "";
}

std::string
stop (chess::engine::Engine &engine, std::string _command)
{
    std::vector<std::string> args;
    std::string command;
    Split (_command, args);

    if (!args.empty ())
        {
            CERR << "Unknown args: " << args[0] << std::endl;
        }

    engine.Stop ();
    CERR << "Engine stopped" << std::endl;
    CERR << "Engine: " << engine.IsStop () << std::endl;
    return "";
}

std::string
isready (chess::engine::Engine &engine, std::string _command)
{
    std::vector<std::string> args;
    std::string command;
    Split (_command, args);

    if (!args.empty ())
        {
            CERR << "Unknown args: " << args[0] << std::endl;
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

    std::vector<std::string> args;
    std::string command;
    Split (_command, args);

    if (!args.empty ())
        {
            CERR << "Unknown args: " << args[0] << std::endl;
        }
    return engine.Search ();
}

std::string
showboard (chess::engine::Engine &engine, std::string _command)
{
    std::vector<std::string> args;
    std::string command;
    Split (_command, args);

    if (!args.empty ())
        {
            CERR << "Unknown args: " << args[0] << std::endl;
        }
    return engine.ShowBoard ();
}

std::string
position (chess::engine::Engine &engine, std::string _command)
{
    std::vector<std::string> args;
    std::string command;
    int offset = 0;
    Split (_command, args);

    if (args[0] == "startpos")
        {
            offset = -5;
            CERR << "Using startpos: " << chess::consts::startpos << std::endl;
            std::string dum = engine.Position (chess::consts::startpos);
        }
    else if (args[0] == "fen")
        {
            offset = 1;
            std::string fen = args[offset] + " " + args[offset + 1] + " " + args[offset + 2] + " " + args[offset + 3] + " " + args[offset + 4] + " " + args[offset + 5];
            CERR << "Using fen: " << fen << std::endl;
            std::string dum = engine.Position (fen);
        }
    else
        {
            std::string fen = args[offset] + " " + args[offset + 1] + " " + args[offset + 2] + " " + args[offset + 3] + " " + args[offset + 4] + " " + args[offset + 5];
            CERR << "Using fen: " << fen << std::endl;
            std::string dum = engine.Position (fen);
        }
    if (args.size () >= (size_t)(6 + offset))
        {
            if (args[6 + offset] == "moves")
                {
                    std::vector<chess::consts::move> moves;
                    for (auto i = (size_t)7 + offset; i < args.size (); i++)
                        {
                            CERR << "Move: " << args[i] << " " << chess::moves::string2move (args[i]) << std::endl;
                            moves.push_back (chess::moves::string2move (args[i]));
                        }
                }
            else
                {
                    CERR << "Unknown args: " << args[6 + offset] << std::endl;
                }
        }
    return "";
}

void
Split (std::string &command, std::vector<std::string> &args)
{

    std::regex re ("([a-zA-Z0-9/-]+)");
    std::sregex_iterator it (command.begin (), command.end (), re);
    command = it->str ();
    while (++it != std::sregex_iterator ())
        {
            std::string arg = it->str ();
            args.push_back (arg.substr (0, arg.size ()));
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
    commands["stop"] = stop;
    commands["isready"] = isready;
    commands["go"] = go;
    commands["showboard"] = showboard;
    commands["position"] = position;
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

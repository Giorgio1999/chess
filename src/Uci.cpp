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
    chess::timer::Timer timer;
    for (uint i = 0; i < args.size (); i++)
        {
            std::string arg = args[i];
            CERR << arg << std::endl;
            if (arg == "wtime")
                {
                    CERR << args[i + 1] << std::endl;
                    timer.SetWtime (std::stoi (args[i + 1]));
                }
            if (arg == "btime")
                {
                    timer.SetBtime (std::stoi (args[i + 1]));
                }
            if (arg == "winc")
                {
                    timer.SetWinc (std::stoi (args[i + 1]));
                }
            if (arg == "binc")
                {
                    timer.SetBinc (std::stoi (args[i + 1]));
                }
        }
    engine.SetTimer (timer);
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
                    for (auto i = (size_t)7 + offset; i < args.size (); i++)
                        {
                            CERR << "Move: " << args[i] << " " << chess::moves::string2move (args[i]) << std::endl;
                            chess::consts::move move = chess::moves::string2move (args[i]);
                            std::string dum = engine.MakeSanitaryMove (move);
                        }
                }
            else
                {
                    CERR << "Unknown args: " << args[6 + offset] << std::endl;
                }
        }
    return "";
}

std::string
perft (chess::engine::Engine &engine, std::string _command)
{
    std::regex re ("([0-9]+)");
    std::sregex_iterator it (_command.begin (), _command.end (), re);
    std::string command = it->str ();
    int depth = std::stoi (command);
    return std::to_string (engine.Perft (depth));
}

std::string
splitperft (chess::engine::Engine &engine, std::string _command)
{
    std::regex re ("([0-9]+)");
    std::sregex_iterator it (_command.begin (), _command.end (), re);
    std::string command = it->str ();
    int depth = std::stoi (command);
    return engine.SplitPerft (depth);
}

std::string
legalmoves (chess::engine::Engine &engine, std::string _command)
{
    return engine.LegalMoves ();
}

std::string
bench (chess::engine::Engine &engine, std::string _command)
{
    return engine.Bench ();
}

std::string
ucinewgame (chess::engine::Engine &engine, std::string _command)
{
    engine.NewGame ();
    return "";
}

std::string
setoption (chess::engine::Engine &engine, std::string _command)
{
    std::vector<std::string> args;
    Split (_command, args);
    engine.SetOption (args);
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
    commands["perft"] = perft;
    commands["splitperft"] = splitperft;
    commands["legalmoves"] = legalmoves;
    commands["bench"] = bench;
    commands["ucinewgame"] = ucinewgame;
    commands["setoption"] = setoption;
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

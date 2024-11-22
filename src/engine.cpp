#include "engine.hpp"
#include "Defs.hpp"
#include "chessConfig.h"
#include "fen.hpp"
#include "moves.hpp"
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
std::string
Engine::Position (std::string _position)
{
    fen::parse (_position, board);
    return "";
}
chess::consts::bitboard
Engine::Perft (int depth)
{
    std::vector<chess::consts::move> legalMoves = moveGenerator.GetLegalMoves (*this);
    if (depth == 0)
        {
            return 1;
        }
    consts::bitboard numberofleafs = 0;
    for (chess::consts::move move : legalMoves)
        {
            std::string dum = MakeMove (move);
            numberofleafs += Perft (depth - 1);
            UndoMove ();
        }
    return numberofleafs;
}
std::string
Engine::SplitPerft (int depth)
{
    std::vector<chess::consts::move> legalMoves = moveGenerator.GetLegalMoves (*this);
    std::string res;
    for (chess::consts::move move : legalMoves)
        {
            res += chess::moves::move2string (move) + std::to_string (Perft (depth - 1)) + "\n";
        }
    return res;
}
std::string
Engine::LegalMoves ()
{
    std::vector<chess::consts::move> legalMoves = moveGenerator.GetLegalMoves (*this);
    std::string res;
    for (chess::consts::move move : legalMoves)
        {
            res += chess::moves::move2string (move) + "\n";
        }
    return res;
}
}
}

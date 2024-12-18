#include "engine.hpp"
#include "Defs.hpp"
#include "chessConfig.h"
#include "fen.hpp"
#include "moves.hpp"
#include "bitboard.hpp"
#include <string>
#include <mutex>
#include <chrono>

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
    out += "id author " + author + "\n";
    out += "option ";
    for (const auto &option : options)
        {
            out += option.second.print () + "\n";
        }
    return out;
}
void
Engine::SetOption (const std::vector<std::string> &args)
{
    options[args[1]].setValue (std::stoi (args[3]));
    update (*this);
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
    currentHash = chess::hash::get_hash (board);
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
    if (depth == 1)
        {
            return legalMoves.size ();
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
            MakeMove (move);
            res += chess::moves::move2string (move) + " " + std::to_string (Perft (depth - 1)) + "\n";
            UndoMove ();
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
std::string
Engine::Bench ()
{
    std::unordered_map<std::string, std::vector<chess::consts::bitboard> > testsuite = chess::consts::getTestSuite ();
    auto start = std::chrono::high_resolution_clock::now ();
    uint64_t leafs = 0;
    for (std::pair<std::string, std::vector<chess::consts::bitboard> > point : testsuite)
        {
            std::string position = point.first;
            std::vector<chess::consts::bitboard> data = point.second;
            for (uint i = 0; i < data.size (); i++)
                {
                    Position (position);
                    leafs += Perft (i);
                }
        }
    auto end = std::chrono::high_resolution_clock::now ();
    auto duration = std::chrono::duration_cast<std::chrono::milliseconds> (end - start).count ();
    return std::to_string (((float)leafs / duration) / 1e6 * 1e3) + " Mnps\n";
}
bool
Engine::IsStalemate ()
{
    bool whiteToPlay = board.white_to_play ();
    chess::consts::Piece coloredKing = whiteToPlay ? chess::consts::Piece::K : chess::consts::Piece::k;
    return (GetAttacks (!whiteToPlay) & board.get_piece_boards ()[coloredKing]) == 0;
}
bool
Engine::IsRepetition ()
{
    return std::count (repetitionTable.begin (), repetitionTable.end (), currentHash) == 2;
}
int
Engine::GetNumberOfRepetitions ()
{
    return std::count (repetitionTable.begin (), repetitionTable.end (), currentHash);
}
bool
Engine::IsMate ()
{
    bool whiteToPlay = board.white_to_play ();
    chess::consts::Piece coloredKing = whiteToPlay ? chess::consts::Piece::K : chess::consts::Piece::k;
    return (GetAttacks (!whiteToPlay) & board.get_piece_boards ()[coloredKing]) > 0;
}
}
}

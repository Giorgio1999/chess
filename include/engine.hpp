#ifndef ENGINE_ENGINE_HPP
#define ENGINE_ENGINE_HPP
#include <string>
#include <functional>
#include "board.hpp"
#include "moveGenerator.hpp"
#include "timer.hpp"
#include "hash.hpp"

namespace chess
{
namespace engine
{
class Engine
{
  private:
    std::string name = "";
    std::string author = "";
    int version_major = 1;
    int version_minor = 0;
    int version_patch = 0;
    std::function<std::string (Engine &)> search;
    bool stop = false;
    bool ready = false;
    chess::board::Board board;
    std::vector<chess::board::Board> gameHistory;
    chess::movegenerator::MoveGenerator moveGenerator;
    chess::timer::Timer timer;
    chess::consts::hash currentHash;
    std::vector<chess::consts::hash> repetitionTable;

  public:
    Engine (std::string name, std::string author)
    {
        this->name = name;
        this->author = author;
        board = chess::board::Board ();
        timer = chess::timer::Timer ();
        chess::hash::init_hash_table ();
        gameHistory.reserve (1000);
        repetitionTable.reserve (1000);
    }

    std::string Introduce ();
    void Stop ();
    void UnStop ();
    chess::consts::bitboard Perft (int depth);
    std::string SplitPerft (int depth);
    std::string LegalMoves ();
    std::string
    Search ()
    {
        return search (*this);
    }
    std::string
    ShowBoard ()
    {
        return board.ShowBoard ();
    }
    std::string Position (std::string _position);
    std::string
    MakeMove (consts::move move)
    {
        gameHistory.push_back (board);
        repetitionTable.push_back (currentHash);
        board.makeMove (move, currentHash);
        return "";
    }
    std::string
    MakeSanitaryMove (consts::move move)
    {
        gameHistory.push_back (board);
        repetitionTable.push_back (currentHash);
        board.sanitize (move);
        board.makeMove (move, currentHash);
        return "";
    }
    std::string Bench ();

    void
    UndoMove ()
    {
        board = gameHistory.back ();
        currentHash = repetitionTable.back ();
        gameHistory.pop_back ();
        repetitionTable.pop_back ();
    }

    void
    NewGame ()
    {
        gameHistory.clear ();
        repetitionTable.clear ();
    }

    std::string
    GetName ()
    {
        return name;
    }
    std::string
    GetAuthor ()
    {
        return author;
    }
    int
    GetVersion_Major ()
    {
        return version_major;
    }
    int
    GetVersion_Minor ()
    {
        return version_minor;
    }
    int
    GetVersion_Patch ()
    {
        return version_patch;
    }
    std::function<std::string (Engine &)>
    GetSearch ()
    {
        return search;
    }
    bool
    IsReady ()
    {
        return ready;
    }
    bool
    IsStop ()
    {
        return stop;
    }

    void
    SetName (std::string _name)
    {
        name = _name;
    }
    void
    SetAuthor (std::string _author)
    {
        author = _author;
    }
    void
    SetVersion_Major (int _version_major)
    {
        version_major = _version_major;
    }
    void
    SetVersion_Minor (int _version_minor)
    {
        version_minor = _version_minor;
    }
    void
    SetVersion_Patch (int _version_patch)
    {
        version_patch = _version_patch;
    }
    void
    SetSearch (std::function<std::string (Engine &)> _search)
    {
        search = _search;
    }
    void
    SetReady (bool _ready)
    {
        ready = _ready;
    }
    chess::board::Board
    GetBoard ()
    {
        return board;
    }
    std::vector<chess::consts::move>
    GetLegalMoves ()
    {
        return this->moveGenerator.GetLegalMoves (*this);
    }
    std::vector<chess::consts::move>
    GetLegalCaptures ()
    {
        return this->moveGenerator.GetLegalCaptures (*this);
    }
    chess::consts::bitboard
    GetAttacks (const bool whiteToPlay)
    {
        return this->moveGenerator.GetAttacks (*this, whiteToPlay);
    }
    chess::timer::Timer
    GetTimer ()
    {
        return this->timer;
    }
    void
    SetTimer (const chess::timer::Timer &_timer)
    {
        this->timer = _timer;
    }
    bool IsStalemate ();
    bool IsRepetition ();
    bool IsMate ();
    chess::consts::hash
    GetCurrentHash ()
    {
        return currentHash;
    }
};

}
}
#endif

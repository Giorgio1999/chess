#include "chess.hpp"
#include <iostream>
#include <chrono>
#include <thread>

class TranspositionTableEntry
{
  public:
    TranspositionTableEntry () { depth = -1; }
    size_t hash;
    int depth;
    bool
    isEmpty () const
    {
        return depth == -1;
    }
    bool
    pushable (const TranspositionTableEntry &b) const
    {
        return true;
    }
    bool
    pullable (const TranspositionTableEntry &b) const
    {
        return b.depth >= depth;
    }
};

chess::transposition::TranspositionTable<TranspositionTableEntry> transpositionTable;

std::string
Search (chess::engine::Engine &engine)
{
    bool whiteToPlay = engine.GetBoard ().white_to_play ();
    std::vector<chess::consts::move> legalMoves = engine.GetLegalMoves ();
    for (chess::consts::move move : legalMoves)
        {
            engine.MakeMove (move);
            TranspositionTableEntry newEntry;
            newEntry.depth = 1;
            newEntry.hash = engine.GetCurrentHash ();
            transpositionTable.push (newEntry);
            engine.UndoMove ();
        }
    std::cout << "info depth 1 hashfull " << (int)((float)transpositionTable.GetFill () / (float)transpositionTable.GetSize () * 1000.) << std::endl;
    return "bestmove " + chess::moves::move2string (legalMoves[0]);
}

void
Update (chess::engine::Engine &engine)
{
    transpositionTable.SetSize (engine.GetOption ("hash"));
}

int
main ()
{
    chess::engine::Engine engine ("example_engine", "example_author");
    engine.SetVersion_Major (1);
    engine.SetVersion_Minor (0);
    engine.SetVersion_Patch (0);
    chess::engine::option hash_option = { "hash", "spin", "64", "0", "10000", "" };
    engine.AddOption (hash_option);
    engine.SetSearch (Search);
    engine.SetUpdate (Update);
    chess::engine::Handler handler (engine, std::cin, std::cout);
    return 0;
}

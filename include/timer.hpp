#ifndef TIMER_HPP_HPP
#define TIMER_HPP_HPP
#include <chrono>

namespace chess
{
namespace timer
{
class Timer
{
  private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start;
    int wtime = 0;
    int btime = 0;
    int winc = 0;
    int binc = 0;

  public:
    Timer () { start = std::chrono::high_resolution_clock::now (); }

    int GetTimeRemaning (const bool whiteToPlay);
    int GetTimeElapsed ();

    void
    SetWtime (const int _wtime)
    {
        wtime = _wtime;
    }
    void
    SetBtime (const int _btime)
    {
        btime = _btime;
    }
    void
    SetWinc (const int _winc)
    {
        winc = _winc;
    }
    void
    SetBinc (const int _binc)
    {
        binc = _binc;
    }

    int
    GetWtime ()
    {
        return wtime;
    }
    int
    GetBtime ()
    {
        return btime;
    }
    int
    GetWinc ()
    {
        return winc;
    }
    int
    GetBinc ()
    {
        return binc;
    }
};
}
}

#endif

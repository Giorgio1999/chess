#include "timer.hpp"

namespace chess
{
namespace timer
{

int
chess::timer::Timer::GetTimeRemaning (const bool whiteToPlay)
{
    auto now = std::chrono::high_resolution_clock::now ();
    auto timePassed = std::chrono::duration_cast<std::chrono::milliseconds> (now - start).count ();
    int timeRemaining = 0;
    if (whiteToPlay)
        {
            timeRemaining = wtime - timePassed + winc;
        }
    else
        {
            timeRemaining = btime - timePassed + binc;
        }
    return timeRemaining;
}
}
}

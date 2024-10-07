#include "chess.hpp"
#include <iostream>
#include <chrono>
#include <thread>

std::string
Search (chess::engine::Engine &engine)
{
    while (engine.IsStop () == false)
        {
            std::cout << "waiting" << std::endl;
            std::this_thread::sleep_for (std::chrono::seconds (1));
        }
    return "TO DO";
}

int
main ()
{
    chess::engine::Engine engine ("example_engine", "example_author");
    engine.SetVersion_Major (1);
    engine.SetVersion_Minor (0);
    engine.SetVersion_Patch (0);
    engine.SetSearch (Search);
    chess::engine::Handler handler (engine, std::cin, std::cout);
    return 0;
}

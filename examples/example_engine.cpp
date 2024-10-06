#include "chess.hpp"
#include <iostream>

std::string
Search (chess::engine::Engine &engine)
{
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
    std::cout << engine.Introduce () << std::endl;
    std::cout << engine.Search () << std::endl;
    return 0;
}

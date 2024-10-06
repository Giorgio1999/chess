#include "chess.hpp"
#include <iostream>

// std::string
// chess::engine::Engine::Search ()
//{
// return "TO DO";
//}

int
main ()
{
    chess::engine::Engine engine ("example_engine", "example_author");
    engine.SetVersion_Major (1);
    engine.SetVersion_Minor (0);
    engine.SetVersion_Patch (0);
    std::cout << engine.Introduce () << std::endl;
    return 0;
}

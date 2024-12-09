#include "chess.hpp"

int
main ()
{
    chess::engine::Engine engine ("Test engine", "Test author");
    std::cout << engine.Bench () << std::endl;
    return 0;
}

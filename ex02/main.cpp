#include "Pmerge.hpp"
#include <iostream>

int main(int argc, char argv**)
{
    if (argc < 2)
    {
        std::cerr << "Error: Input numbers to sort\n";
        return 1;
    }

    checkInput(argv + 1);
}
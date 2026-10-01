#include "PmergeMe.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: Input numbers to sort\n";
        return 1;
    }
 
    PmergeMe obj;

    if (!obj.checkInput(argv + 1))
    {
        std::cerr << "Error" << std::endl;
        return 1;
    }

    obj.sort(argv + 1);

}
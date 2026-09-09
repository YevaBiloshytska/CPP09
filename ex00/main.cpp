#include "BitcoinExchange.hpp"

#include <string>
#include <iostream>
#include <fstream>

int main(int argc, char **argv)
{
    BitcoinExchange obj;

    if (argc != 2)
    {
        std::cerr << "Error: could not open file." << std::endl;
        return 1;
    }

    try
    {
        obj.readFile(argv[1]);
    }
    catch(std::exception &e)
    {
        std::cout << e.what() << std::endl;
    }
   // obj.checkFormat();
}
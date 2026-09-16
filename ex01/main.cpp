#include "RPN.hpp"
#include <iostream>

int main(int argc, char **argv)
{
    if (argc != 2)
    {
        std::cerr << "Usage: ./RPN \"x y + ... \"\n";
        return 1;
    }
    
    RPN obj;
    if(!obj.checkFormat(argv[1]))
        return 1;

    obj.fillStack(argv[1]);
}

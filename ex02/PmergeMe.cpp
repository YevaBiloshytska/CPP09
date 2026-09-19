#include "PmergeMe.hpp"

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &obj)
{
    *this = obj;
}
PmergeMe & PmergeMe::operator=(const PmergeMe &rhs)
{
    if (this != &rhs)
    {
        vector = rhs.vector;
        dqueu = rhs.dqueu;
    }
    return *this;
}
PmergeMe::~PmergeMe() {}

bool PmergeMe::checkInput (char **argv)
{
    int number;
    for (int i = 0; argv[i]; i++)
    {
        for(int j = 0; argv[j]; j++)
        {
            if(!isdigit(argv[i][j]))
                return false;
        }
        number = atoi(argv[i]);
        if (number < 1 || number > INT_MAX)
            return false;
    }
    return true;
}
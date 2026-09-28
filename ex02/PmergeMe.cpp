#include "PmergeMe.hpp"
#include <cctype> //isdigit
#include <cstdlib> //atoi, strtol
#include <climits>
#include <cerrno>
#include <iostream>
#include <utility> //pair

PmergeMe::PmergeMe() {}
PmergeMe::PmergeMe(const PmergeMe &obj)
{
    *this = obj;
}
PmergeMe & PmergeMe::operator=(const PmergeMe &rhs)
{
    if (this != &rhs)
    {
        _vector = rhs._vector;
        _deque = rhs._deque;
    }
    return *this;
}
PmergeMe::~PmergeMe() {}

bool PmergeMe::checkInput (char **argv)
{
    long number;
    for (int i = 0; argv[i]; i++)
    {
        for(int j = 0; argv[i][j]; j++)
            if (!std::isdigit(static_cast<unsigned char>(argv[i][j])))
                return false;
        errno = 0;
        number = std::strtol(argv[i], NULL, 10);
        if (errno == ERANGE)
            return false;
        if (number < 1 || number > INT_MAX)
            return false;
    }

    return true;
}

int f =0;

template <typename T>
void PmergeMe::fordJohnsonVector(T & vec)
{
    size_t size = vec.size();

    // if (size % 2)
    // {
    //     int straggler = _vector.back();
    // }
    std::vector< std::pair<int, int> > firstPairs;
    if(size == _vector.size() || size == _vector.size() - 1)
    {
        for(size_t i = 0; i < size - 1; i++)
        {
            firstPairs.push_back(std::make_pair(vec[i], vec[i + 1]));
            i = i + 1;
        }
        f++;
    }

    // for (size_t i = 0; i < firstPairs.size(); i++)
    // {
    //     std::cout << "[" << firstPairs[i].first
    //             << ", " << firstPairs[i].second << "] ";
    // }

    std::vector< std::pair<int, int> > pairs;

    for(size_t i = 0; i < size - 1; i++)
    {
        pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
        i = i + 1;
    }

    std::cout << "Here a new vector: \n";
    for (size_t i = 0; i < pairs.size(); i++)
    {
        std::cout << "[" << pairs[i].first
                << ", " << pairs[i].second << "] ";
    }


    std::vector<int> recVector;

    for(size_t i = 0; i < pairs.size(); i++)
    {
        if(pairs[i].first > pairs[i].second)
        {
            int tmp = pairs[i].second;
            pairs[i].second = pairs[i].first;
            pairs[i].first = tmp;
        }
        recVector.push_back(pairs[i].second);
    }

    std::cout << "\nafter sorting:\n";
    for (size_t i = 0; i < pairs.size(); i++)
    {
        std::cout << "[" << pairs[i].first
                << ", " << pairs[i].second << "] ";
    }
    std::cout << std::endl;
    std::cout << "second numbers: ";
    for(size_t i = 0; i < recVector.size(); i++)
    {
        std::cout << recVector[i] << ", ";
    }
    std::cout << std::endl;

    if (recVector.size() >= 2)
        fordJohnsonVector(recVector);

    std::cout << std::endl;
    for (size_t i = 0; i < firstPairs.size(); i++)
    {
        std::cout << "[" << firstPairs[i].first
                << ", " << firstPairs[i].second << "] ";
    }
    std::cout << std::endl;

}


void PmergeMe::sort(char **argv)
{
    // START vector timer
    fillContainer(_vector, argv);
    fordJohnsonVector(_vector);
    // STOP vector timer

    //// START deque timer
    // fillContainer(_deque, argv);
    // fordJohnsonDeque(_deque);
    //// STOP deque timer
}



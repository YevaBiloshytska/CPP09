#include "PmergeMe.hpp"
#include <cctype> //isdigit
#include <cstdlib> //atoi, strtol
#include <climits>
#include <cerrno>
#include <iostream>
#include <utility> //pair
#include <algorithm>// find
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

int getJacobsthalNumber(int i)
{
    long long j0 = 1;
    long long j1 = 3;

    for (int n = 0; n < i; n++)
    {
        long long next = j1 + 2 * j0;
        j0 = j1;
        j1 = next;
    }

    return j0;
}

static std::vector<int>::iterator binarySearch(std::vector<int> & vector, int target, std::vector<int>::iterator right)
{
    std::vector<int>::iterator left = vector.begin();
    std::vector<int>::iterator mid;
    //int right = vector.size();

    while (left != right)
    {
        mid = left + (right - left) / 2;
        if (target > *mid)
            left = mid + 1;
        else
            right = mid;
    }

    return left;
}

// #include <cmath>
// static int getArrange(int compare)//type?
// {
//     return std::pow(2, compare) - 1;
// }

template <typename T>
std::vector<int> PmergeMe::fordJohnsonVector(T & vec)
{
    size_t size = vec.size();
    int straggler = 0;

    std::vector<int> mainChain;
    std::vector< std::pair<int, int> > firstPairs;
    std::vector< std::pair<int, int> > pairs;

    if (size % 2)
        straggler = vec.back();
    std::cout << "Stragler: " << straggler << std::endl;

    
    for(size_t i = 0; i + 1 < size; i += 2)
    {
        pairs.push_back(std::make_pair(vec[i], vec[i + 1]));
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
    
    std::cout << "after sorting:\n";
    for (size_t i = 0; i < pairs.size(); i++)
    {
        std::cout << "[" << pairs[i].first
                << ", " << pairs[i].second << "] ";
    }

    if(size == _vector.size() || size == _vector.size() - 1)
        firstPairs = pairs;

    std::cout << std::endl;

    std::cout << "second numbers: ";
    for(size_t i = 0; i < recVector.size(); i++)
    {
        std::cout << recVector[i] << ", ";
    }
    std::cout << std::endl;

    if (recVector.size() >= 2)
        mainChain = fordJohnsonVector(recVector);
    else
        mainChain = recVector;

    std::cout << "__________________________________________________\nGet out from recursy: " << std::endl;

    std::cout << "mainChain: ";
    for(size_t i = 0; i < mainChain.size(); i++)
    {
        std::cout << mainChain[i] << ", ";
    }



    std::cout << std::endl;
    std::cout << "pairs: ";
    for (size_t i = 0; i < pairs.size(); i++)
    {
        std::cout << "[" << pairs[i].first
                << ", " << pairs[i].second << "] ";
    }
    std::cout << std::endl;

    std::vector< std::pair<int, int> > sortedPairs;
    for(size_t i = 0; i < mainChain.size(); i++)
    {
        for(size_t j = 0; j < pairs.size(); j++)
        {
            if (pairs[j].second == mainChain[i])
            {
                sortedPairs.push_back(pairs[j]);
                break;
            }
        }
    }

    std::cout << "Sorted pairs: ";
    for (size_t i = 0; i < sortedPairs.size(); i++)
    {
        std::cout << "[" << sortedPairs[i].first
                << ", " << sortedPairs[i].second << "] ";
    }
    std::cout << std::endl;

    for(size_t i = 0; i < sortedPairs.size(); i++)//проxодимся по всем парам [7, 9] [6, 13] [21, 43] [4, 23] [5, 32] [3, 8] [7, 9]
    {
        std::cout << "Цикл for (проход по парам [b1 a1] [b2 a2]...), i = " << i << std::endl;
        size_t border = getJacobsthalNumber(i);//1 3 5 11
        std::cout << "JacobsthalNumber(border) = " << border << std::endl;
        //int arrangeForSearchAi = getArrange(i + 1);//1 3 7 15
        if (i == 0)
        {
            std::cout << "Я вставляю b1 в цепочку\n";
            mainChain.insert(mainChain.begin(), sortedPairs[i].first);
            std::cout << "mainChain: ";
            for(size_t i = 0; i < mainChain.size(); i++)
            {
                std::cout << mainChain[i] << ", ";
            } 
            std::cout << std::endl;
        }
        else if(i < border) //[7, 9] [6, 13] [21, 43] [25, 53] = 1 // 2 (index) < 3 // 5 
        {
            std::cout << "проходимся по следующим парам, где i = " << i << std::endl;
            while (i < border && i < sortedPairs.size())//1, 3 ,5, 11 ... границы для (b1 a1 a2 a3 a4 a5..) = a3 a5 a11
            {
                int a_index = sortedPairs.size() - i; //iterator better
                if(a_index >= getJacobsthalNumber(i))
                    a_index = getJacobsthalNumber(i);
                //
                    //iterator = begin + sortedPairs.size()
                // else
                // ....
                std::vector<int>::iterator it = std::find(mainChain.begin() + 1 + getJacobsthalNumber(i - 1), mainChain.begin() + border, sortedPairs[a_index].second);//getArrange сделать итератором
                std::cout<< "i = " << i << "; range for search: [" << getJacobsthalNumber(i - 1) << ", " << getJacobsthalNumber(i) << "]\n";
                std::cout << "found *it = " << *it << std::endl;

                std::vector<int>::iterator index = binarySearch(mainChain, sortedPairs[2].first, it);
                std::cout << "Insert: " << sortedPairs[sortedPairs.size() - i - 1].first << std::endl;
                mainChain.insert(index, sortedPairs[sortedPairs.size() - i - 1].first);
                i++;
            }
        }

    }

    // std::cout << "mainChain: ";
    // for(size_t i = 0; i < mainChain.size(); i++)
    // {
    //     std::cout << mainChain[i] << ", ";
    // }
    // std::cout << std::endl;
    std::cout << std::endl;
    // if (straggler)
    // {
    //     int index = binarySearch(recVector, straggler);
    //     recVector.insert(recVector.begin() + index, straggler);
    // }
    std::cout << std::endl;

    for (size_t i = 0; i < firstPairs.size(); i++)
    {
        std::cout << "[" << firstPairs[i].first
                << ", " << firstPairs[i].second << "] ";
    }
    return mainChain;
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


//  ./PmergeMe 53 25 23 4 32 5 3 8 7 9 6 13 2 1 43 21

    // int j = mainChain.size() - 1;//1
    // std::vector<int> mainChainCopy = mainChain;
    // while(j >= 0) //53 //43
    // {
    //     for(size_t i = 0; i < pairs.size(); i++) //[32, 53]    //[13, 43] 
    //     {
    //         // std::cout << "pairs[i].second = " << pairs[i].second << std::endl;
    //         // std::cout << "mainChainCopy = " << mainChainCopy[j] << std::endl;
    //         if(pairs[i].second == mainChainCopy[j]) //как обезопасить себя от повтора числа?
    //         {
    //             std::vector<int>::iterator it = std::find(mainChain.begin(), mainChain.end(), mainChainCopy[j]);
    //             std::vector<int>::iterator index = binarySearch(mainChain, pairs[i].first, it); //before a1 (change binarySearch)
    //             mainChain.insert(index, pairs[i].first);
    //             std::cout << "next insert is: " << pairs[i].first << std::endl;
    //             break;
    //         }
    //     }
    //     j--;
    // }
    
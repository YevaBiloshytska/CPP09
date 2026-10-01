#ifndef PMERGE_HPP
# define PMERGE_HPP

# include <vector>
# include <deque>
# include <cstdlib>

class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(const PmergeMe &obj);
    PmergeMe & operator=(const PmergeMe &rhs);
    ~PmergeMe();

    bool checkInput (char **argv);
    void sort(char **argv); 
    
private:
    std::vector<int> _vector;
    std::deque<int> _deque;
    template <typename T>
    std::vector<int> fordJohnsonVector(T & vec);
    void fordJohnsonDeque();
    template <typename T>
    void fillContainer(T&container, char **argv);
};

template <typename T>
void PmergeMe::fillContainer(T& container, char **argv)
{
    int number;
    for (int i = 0; argv[i]; i++)
    {
        number = atoi(argv[i]);
        container.push_back(number);
    }
}

#endif
#ifndef PMERGE_HPP
# define PMERGE_HPP

# include <vector>
# include <dqueu>

class PmergeMe
{
public:
    PmergeMe();
    PmergeMe(const PmergeMe &obj);
    PmergeMe & operator=(const PmergeMe &rhs);
    ~PmergeMe();

    bool checkInput (char **argv);

private:
    std::vector<int> vector;
    std::dqueu<int> dqueu;
}


#endif
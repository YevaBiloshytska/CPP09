#ifndef RPN_HPP
# define RPN_HPP

# include <stack>
# include <iostream>
# include <string>

class RPN
{
public:
    RPN();
    RPN(const RPN &obj);
    RPN &operator=(const RPN &rhs);
    ~RPN();

    void fillStack(const char *input);
    bool checkFormat(const char * input);
    int calculate(int r, int l, char op);
private:
    std::stack<int> polNot;
};

#endif
#include "RPN.hpp"
#include <cctype>
#include <sstream>
#include <string>

RPN::RPN(){}

RPN::RPN(const RPN &obj)
{
    *this = obj;
}

RPN &RPN::operator=(const RPN &rhs)
{
    if (this != &rhs)
        polNot = rhs.polNot;
    return *this;
}

RPN::~RPN(){}

static bool isDivisionByNull(int r, char op)
{
    if (r == 0 && op == '/')
        return true;
    return false;
}

int RPN::calculate(int r, int l, char op)
{
    switch(op)
    {
        case '+':
            return l + r;
        case '-':
            return l - r;
        case '/':
            return l / r;
        case '*':
            return l * r;
    }
    return 0;
}

void RPN::fillStack(const char *input)
{
    std::string str(input);
    std::istringstream stream(input);//создай поток stream, который будет читать данные из строки str
    std::string token;

    const std::string operators = "/*+-";
    int number;
    int right;
    int left;
    int result;
    while (stream >> token)
    {
        if (std::isdigit(token[0]))
        {
            number = token[0] - '0';
            polNot.push(number);
        }
        else if (operators.find(token) != std::string::npos && polNot.size() > 1)
        {

            if(isDivisionByNull(polNot.top(), token[0]))
            {
                std::cerr << "Error\n";
                return;
            }
            right = polNot.top();
            polNot.pop();

            left = polNot.top();
            polNot.pop();

            result = calculate(right, left, token[0]);
            polNot.push(result);
        }
        else
        {
            std::cerr << "Error\n";
            return;
        }
    }
    if (polNot.size() != 1)
    {
        std::cerr << "Error\n";
        return;
    }
    std::cout << polNot.top() << std::endl;
}

bool RPN::checkFormat(const char *input)
{
    std::string str(input);

    size_t strSize = str.size();

    if(strSize < 5 || strSize % 2 == 0 || str[strSize - 1] == ' ')
    {
        std::cerr << "Error\n";
        return false;
    }

    for(size_t i = 0; i < strSize - 1; i++)
    {
        if(str[i] != ' ' && str[i+1] == ' ')
            i++;
        else
        {
            std::cerr << "Error\n";
            return false;
        }
    }
    return true;
}



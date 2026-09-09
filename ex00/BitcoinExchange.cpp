#include "BitcoinExchange.hpp"
#include <exception>
BitcoinExchange::BitcoinExchange(){}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &obj) //rewrite
{
    *this = obj;
}

BitcoinExchange BitcoinExchange::operator=(const BitcoinExchange &rhs)//rewrite 
{
    if (this != &rhs)
        this->_file = rhs._file;

    return *this;
}

BitcoinExchange::~BitcoinExchange(){}

void BitcoinExchange::checkFirstLine()
{
    std::string firstLine = "date | value";

    if (_file == firstLine)
        std::cout << "YES!\n";
    else
        throw std::runtime_error("ERROR: File's format is invalid\n");
}

static bool isAllnum(std::string str)
{
    while(*str)
    {
        if (*str.isdigit())
            str++;
        else
            return false;
        // else
        //     throw std::time_error("ERROR: inappropriate symbol");
    }
    return true;
}

static void devideDate(std::string date, std::string month, std::string day)
{

}

void BitcoinExchange::checkDate()
{
    

}

void BitcoinExchange::readFile(const char *ptr)
{
    std::ifstream input(ptr);
    bool firstLine = true;
    while (getline(input, _file))
    {
        if(firstLine)
        {
            checkFirstLine();
            firstLine = false;
        }


    }
    input.close();
}



//После того, как напишу код через вынес сначала в string текст, 
//а потом проверки строк, можно будет эту валидацию сделать сразу после открытия файла.
//нет, потому что нам нужно переписывать файл, который мы будем выводить, поэтому
//лучше его хранить в стоке.








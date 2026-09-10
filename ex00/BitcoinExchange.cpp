#include "BitcoinExchange.hpp"
#include <exception>
#include <cctype> //isdigit
#include <cstdlib>  //std::atoi()

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
    if (_file != "date | value")
        throw std::runtime_error("ERROR: File's format is invalid\n");
}

static bool isAllnum(std::string str)
{
    for(size_t i = 0; i < str.size(); i++)
        if(!std::isdigit(str[i]))
            return false;
    return true;
}

static void checkGregorianCalender(int year, int month, int day)
{
    if (year < 1 || (month < 1 || month > 12) || (day < 1 || day > 31))
        throw std::runtime_error("Error: out of range year/month/day => ");

    if (!((year % 400 == 0) || (year % 4 == 0 && year % 100 != 0)))
    {
        if(month == 2 && day > 28)
            throw std::runtime_error("Error: February is till 28 this year => ");
    }
    else
    {
        if(month == 2 && day > 29)
            throw std::runtime_error("Error: February is till 29 this year => ");
    }

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day == 31)
        throw std::runtime_error("Error: This month is till 30 => ");
}

void BitcoinExchange::checkDate()
{
    std::string::size_type posYearEnd = _file.find('-');
    std::string::size_type posMonthEnd = _file.find('-', posYearEnd + 1);
    std::string::size_type posDayEnd = _file.find(' ', posMonthEnd + 1);

    if (posYearEnd != 4 || posMonthEnd != 7 || posDayEnd != 10)
        throw std::runtime_error("Error: bad input => ");

    std::string yearStr = _file.substr(0, 4);
    std::string monthStr = _file.substr(posYearEnd + 1, 2);
    std::string dayStr = _file.substr(posMonthEnd + 1, 2);

    if (!(isAllnum(yearStr) && isAllnum(monthStr) && isAllnum(dayStr)))
        throw std::runtime_error("Error: bad input => ");

    int year = std::atoi(yearStr.c_str());
    int month = std::atoi(monthStr.c_str());
    int day = std::atoi(dayStr.c_str());

    try
    {
        checkGregorianCalender(year, month, day);
    }
    catch(std::exception &e)
    {
        std::cout << e.what();
    }
}


void BitcoinExchange::checkValue()
{

    std::string value = _file.substr(13, _file.size() - 13);

    float v = std::atof(value.c_str());
    if (v < 0)
        throw std::runtime_error("Error: not a positive number.\n");
    if (v > 1000)
        throw std::runtime_error("Error: too large a number.\n");
   
}

void BitcoinExchange::checkLine()
{
    checkDate();
    std::cout << _file << "\n";
    std::string::size_type between = _file.find(" | ");
    if (between != 10)
        throw std::runtime_error("Error: invalid input => ");
    checkValue();
}

void BitcoinExchange::readFile(const char *ptr)
{
    std::ifstream input(ptr);
    getline(input, _file);
    checkFirstLine();
    while (getline(input, _file))
    {
        try
        {
            checkLine();
        }
        catch(std::exception &e)
        {
            std::cout << e.what();
        } 
    }
    input.close();
}



//После того, как напишу код через вынес сначала в string текст, 
//а потом проверки строк, можно будет эту валидацию сделать сразу после открытия файла.
//нет, потому что нам нужно переписывать файл, который мы будем выводить, поэтому
//лучше его хранить в стоке.








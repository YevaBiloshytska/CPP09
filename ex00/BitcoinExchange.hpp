#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <string>
# include <map>

class BitcoinExchange
{
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &obj);
    BitcoinExchange operator=(const BitcoinExchange &rhs);
    ~BitcoinExchange();

    void readFile(const char *input);
    void checkFirstLine();
    void checkLine();
    void checkDate();
    void checkValue();

    void createContainer();
    
private:
    std::string _file;
    int outputCounter;
    std::string date;
    double val;
    std::map<std::string, double>;
};


#endif

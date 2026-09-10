#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>
# include <string>
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
    
private:
    std::string _file;
};


#endif

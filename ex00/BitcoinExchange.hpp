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

    void checkFirstLine();
    void readFile(const char *input);
    void checkDate();
    
private:
    std::string _file;
};


#endif

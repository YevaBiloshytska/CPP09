#ifndef BITCOINEXCHANGE_HPP
# define BITCOINEXCHANGE_HPP

# include <iostream>
# include <fstream>

class BitcoinExchange
{
public:
    BitcoinExchange();
    BitcoinExchange(const BitcoinExchange &obj);
    BitcoinExchange operator=(const BitcoinExchange &rhs);
    ~BitcoinExchange();

private:
    std::ifstream _file;

    
}


#endif

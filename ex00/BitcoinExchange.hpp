#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <cmath>
#include <map>
#include <string>
#include <sstream>


// よく分かってない：
/* なぜmapだと効率よく直前の日付を探せるのか？*/

class BitcoinExchange
{
	private:
		std::map<std::string, double> _rates;

		void loadDatabase(const std::string &filename);
		double findRate(const std::string &date) const;
	
	public:
		BitcoinExchange();
		BitcoinExchange(const std::string &databaseFile);
		BitcoinExchange(const BitcoinExchange &other);
		~BitcoinExchange();

		BitcoinExchange &operator=(const BitcoinExchange &other);

		
		void processInputFile(const std::string &filename) const;
};


#endif
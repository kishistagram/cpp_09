#include "BitcoinExchange.hpp"

static std::string trim(const std::string &str);
static bool isLeapYear(int year);
static bool isValidDate(const std::string &date);
static bool parseNumber(const std::string &str, double &value);

// helper functions
static std::string trim(const std::string &str)
{
	const std::string whitespace = " \t\r\n";

	std::string::size_type start =
		str.find_first_not_of(whitespace);
	if (start == std::string::npos)
		return "";
	
	std::string::size_type end =
		str.find_last_not_of(whitespace);
	
	return str.substr(start, end - start + 1);
}

static bool isLeapYear(int year)
{
	return (year % 400 == 0 ||
			(year % 4 == 0 && year % 100 != 0));
}

static bool isValidDate(const std::string &date)
{
	if (date.length() != 10)
		return false;
	if (date[4] != '-' || date[7] != '-')
		return false;
	
	for (std::size_t i = 0; i < date.length(); ++i)
	{
		if (i == 4 || i == 7)
			continue;
		
		if (!std::isdigit(static_cast<unsigned char>(date[i])))
			return false;
	}

	int year;
	int month;
	int day;

	year = std::atoi(date.substr(0, 4).c_str());
	month = std::atoi(date.substr(5, 2).c_str());
	day = std::atoi(date.substr(8, 2).c_str());

	if (year < 1 || month < 1 || month > 12)
		return false;
	
	const int dayInMonth[12] = {
		31, 28, 31, 30, 31, 30,
		31, 31, 30, 31, 30, 31
	};

	int maxDay = dayInMonth[month - 1];

	if (month == 2 && isLeapYear(year))
		maxDay = 29;
	
	return(day >= 1 && day <= maxDay);

}

// constructors / destructor / operator overload

BitcoinExchange::BitcoinExchange()
{
	loadDatabase("data.csv");
}

BitcoinExchange::BitcoinExchange(const std::string &databaseFile)
{
	loadDatabase(databaseFile);
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &other)
	: _rates(other._rates)
{
}

BitcoinExchange::~BitcoinExchange() {}

BitcoinExchange &BitcoinExchange::operator=(const BitcoinExchange &other)
{
	if (this != &other)
		_rates = other._rates;
	return (*this);
}

// Load database 

/*
loadDatabase()の責務は？
-> CSVファイルを読み込み、日付をkey、ビットコイン価格をvalueとして_rateに格納する

1. CSVファイルを開く
2. ヘッダーを読み飛ばす、確認をする
3. データを１行ずつ読み込む
4. ,で日付と価格を分割
5. 日付と数値を検証
6. std::mapに登録する


データ行の処理について：
1. カンマの位置を探す
2. 日付と価格の文字列を取り出す
3. 日付が正しいか検証する
4. 価格をdoubleへ変換する
5. 価格がnegativeではないか検証する
6. newRatesへinsertする

*/
void BitcoinExchange::loadDatabase(const std::string &filename)
{
	std::ifstream file(filename.c_str());

	if (!file.is_open())
		throw std::runtime_error("could not open database file");
	
	std::string line;

	// csvヘッダを読む
	if (!std::getline(file, line))
		throw std::runtime_error("empty database file");
	
	if (trim(line) != "date,exchange_rate")
		throw std::runtime_error("invalid database header");

	// Temporary container
	std::map<std::string, double> newRates;
	
	// データ行を処理する
	while (std::getline(file, line))
	{
		// カンマを探す
		std::string::size_type comma_pos = line.find(',');

		if (comma_pos == std::string::npos ||
			line.find(',', comma_pos + 1) != std::string::npos)
			throw std::runtime_error("invalid database row");

		// 日付、rateをそれぞれ取り出す
		std::string date = trim(line.substr(0, comma_pos));
		std::string rateStr = trim(line.substr(comma_pos + 1));

		// validate date
		if (!isValidDate(date))
			throw std::runtime_error("invalid databse date");
		
		// convert & validate exchange rate
		double rate;

		if (!parseNumber(rateStr, rate) || rate < 0)
			throw std::runtime_error("invalid exchange date");

		if (!newRates.insert(std::make_pair(date, rate)).second)
			throw std::runtime_error("duplicate database date");
	}

	if (file.bad())
		throw std::runtime_error("database read error");
	
	if (newRates.empty())
		throw std::runtime_error("database is empty");
	
	// Commit only after successful loading
	_rates.swap(newRates);
}

double BitcoinExchange::findRate(const std::string &date) const
{
	if (_rates.empty())
		throw std::runtime_error("database is empty");
	
	std::map<std::string, double>::const_iterator it;

	it = _rates.upper_bound(date);

	if (it == _rates.begin())
		throw std::runtime_error("no earlier date available");
	
	--it;
	return it->second;
}



// 
static bool parseNumber(const std::string &str, double &value)
{
	std::stringstream ss(str);
	ss >> value;
	if (ss.fail())
		return false;
	ss >> std::ws;

	return ss.eof();
}


void BitcoinExchange::processInputFile(const std::string &filename) const
{
	std::ifstream file(filename.c_str());

	if (!file.is_open())
		throw std::runtime_error("could not open file");
	/* ファイルエラーの種類 */
	// could not open file

	// empty input
	std::string line;
	if (!std::getline(file, line))
		throw std::runtime_error("empty input file");

	if (trim(line) != "date | value")
		throw std::runtime_error("invalid input header");
	// invalid input header とか？

	while (std::getline(file, line))
	{
		std::string::size_type pos = line.find('|');

		if (pos == std::string::npos || line.find('|', pos + 1) != std::string::npos)
		{
			std::cerr << "Error: bad input => "
					  << line << std::endl;
			continue;
		}
		std::string date = trim(line.substr(0, pos));
		std::string valueStr = trim(line.substr(pos + 1));

		if (!isValidDate(date))
		{
			std::cerr << "Error: bad input => "
					  << line << std::endl;
			continue;
		}

		double value;

		if (!parseNumber(valueStr, value))
		{
			std::cerr << "Error: bad input => "
					  << line << std::endl;
			continue;
		}

		if (value < 0)
		{
			std::cerr << "Error: not a positive number."
					  << std::endl;
			continue;
		}

		if (value > 1000)
		{
			std::cerr << "Error: too large a number."
					  << std::endl;
			continue;
		}

		try
		{
			double rate = findRate(date);

			std::cout << date << " => "
					  << value << " = "
					  << value * rate << std::endl;
		}
		catch(const std::exception& e)
		{
			std::cerr << "Error: " << e.what()
					  << std::endl;
		}
		


	}

	if (file.bad())
		throw std::runtime_error("input file read error");


	// bad input
	// ...

}


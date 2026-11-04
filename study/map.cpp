#include <iostream>
#include <map>
#include <string>

int main()
{
	std::map<std::string, double> rates;

    // わざと日付をバラバラの順番で挿入
	rates["hello"] = -500.0;
    rates["2020-01-01"] = 7200.0;
    rates["2011-01-03"] = 0.3;
    rates["2015-06-10"] = 230.0;
    rates["2012-01-11"] = 7.1;


    for (std::map<std::string, double>::const_iterator it = rates.begin();
         it != rates.end(); ++it)
    {
        std::cout << it->first << " : "
                  << it->second << std::endl;
    }
	
}
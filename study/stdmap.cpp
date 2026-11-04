#include <map>
#include <iostream>
#include <string>
#include <utility>

int main()
{
	std::map<std::string, float> w;
	
	w["H"] = 1.00f;
	w["O"] = 15.99f;
	w["Cl"] = 34.97f;
	w["Na"] = 22.99f;
	
	w.insert(std::make_pair("K", 38.10f));

	// for (const std::pair<const std::string, int> &item : w)
	for (std::map<std::string, float>::const_iterator it = w.begin();
		it != w.end(); ++it)
	{
		std::cout << it->first << ": "  << it->second << std::endl;
	}

	std::cout << "NaOH: " 
			  << w["Na"] + w["O"] + w["H"]
			  << std::endl;

}
#include <iostream>
#include <vector>
#include <stdexcept>
#include <climits>

static int parsePositiveInt(const char *str)
{
    if (*str == '\0')
        throw std::runtime_error("empty argument");
    
    int value = 0;

    for (int i = 0; str[i] != '\0'; ++i)
    {
        if (str[i] < '0' || str[i] > '9')
            throw std::runtime_error("invalid positive integer");
        
        int digit = str[i] - '0';

        if (value > (INT_MAX - digit) / 10)
            throw std::runtime_error("integer overflow");
        
        value = value * 10 + digit;
    }
    if (value == 0)
        throw std::runtime_error("integet must be positive");
    return value;
}

static void printNumbers(const std::vector<int> &numbers)
{
    for (std::vector<int>::const_iterator it = numbers.begin(); it!= numbers.end(); ++it)
    {
        if (it != numbers.begin())
            std::cout << " ";
        std::cout << *it;
    }
    std::cout << std::endl;
}


int main(int argc, char **argv)
{
    if (argc < 2)
    {
        std::cerr << "Error: provide positive integers" << std::endl;
        return 1;

    }
    try
    {
        std::vector<int> numbers;

        for (int i = 1; i < argc; ++i)
            numbers.push_back(parsePositiveInt(argv[i]));

        std::cout << "Before: ";
        printNumbers(numbers);
    }
    catch (const std::exception &e)
    {
        std::cerr << "Error: " << e.what() << std::endl;
        return 1;
    }

    return 0;
}

#include "PmergeMe.hpp"


// 共通のもの
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

PmergeMe::PmergeMe() {}

PmergeMe::PmergeMe(const PmergeMe &other)
    : _vector(other._vector), _deque(other._deque)
{
}

PmergeMe &PmergeMe::operator=(const PmergeMe &other)
{
    if (this != &other)
    {
        _vector = other._vector;
        _deque = other._deque;
    }
    return *this;
}

PmergeMe::~PmergeMe() {}

void PmergeMe::loadVector(int argc, char **argv)
{
    _vector.clear();

    for (int i = 1; i < argc; ++i)
        _vector.push_back(parsePositiveInt(argv[i]));

}

void PmergeMe::loadDeque(int argc, char **argv)
{
    _deque.clear();

    for (int i = 1; i < argc; ++i)
        _deque.push_back(parsePositiveInt(argv[i]));
}

void PmergeMe::run(int argc, char **argv)
{
    if (argc < 2)
        throw std::runtime_error("provide positve integer");

    loadVector(argc, argv);
    loadDeque(argc, argv);

    // 確認用
    std::cout << "Vector: ";
    for (std::vector<int>::size_type i = 0; i < _deque.size(); ++i)
        std::cout << " " << _vector[i];
    std::cout << std::endl;

    std::cout << "Deque: ";
    for (std::deque<int>::size_type i = 0; i < _deque.size(); ++i)
        std::cout << " " << _deque[i];
    std::cout << std::endl;
}




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
// constructor & destructor
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

// private func
void PmergeMe::loadDeque(int argc, char **argv)
{
    _deque.clear();

    for (int i = 1; i < argc; ++i)
        _deque.push_back(parsePositiveInt(argv[i]));
}

// ２個ずつ取り出す　-> 大小を比較　-> ペアとして保存
void PmergeMe::makeVectorPairs(
    std::vector<std::pair<int, int> > &pairs,
    bool &hasStraggler,
    int &straggler) const
{
    pairs.clear();
    hasStraggler = false;
    straggler = 0;

    std::vector<int>::size_type i = 0;

    while (i + 1 < _vector.size())
    {
        int smaller = _vector[i];
        int larger  = _vector[i + 1];

        if (smaller > larger)
            std::swap(smaller, larger);
        
        pairs.push_back(std::make_pair(smaller, larger));
        i += 2;
    }
    if (i < _vector.size())
    {
        hasStraggler = true;
        straggler = _vector[i];
    }
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
    
    std::vector<std::pair<int, int> > pairs;
    bool hasStraggler;
    int straggler;

    makeVectorPairs(pairs, hasStraggler, straggler);

    std::cout << "Pairs:";
    for (std::vector<std::pair<int, int> >::size_type i = 0;
        i < pairs.size(); ++i)
    {
        std::cout << " (" << pairs[i].first 
            << ", " << pairs[i].second << ")";
    }
    std::cout << std::endl;
    
    if (hasStraggler)
        std::cout << "Straggler: " << straggler << std::endl;
}




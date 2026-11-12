#include "PmergeMe.hpp"

#include <iostream>
#include <stdexcept>
#include <climits>
#include <algorithm>
#include <utility>


#define RED   "\033[0;31m"
#define RESET "\033[0m"

// ============================================================
// Input validation
// ============================================================

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
        throw std::runtime_error("integer must be positive");

    return value;
}

// ============================================================
// Orthodox Canonical Form
// ============================================================

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

// ============================================================
// Load containers
// ============================================================

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

// ============================================================
// Group helpers
// ============================================================

// Return the representative (last element) of a group.
static int groupMax(
    const std::vector<int> &data,
    std::size_t start,
    std::size_t size)
{
    return data[start + size - 1];
}

// Append an entire group to another vector.
static void appendGroup(
    std::vector<int> &out,
    const std::vector<int> &data,
    std::size_t start,
    std::size_t size)
{
    out.insert(
        out.end(),
        data.begin() + start,
        data.begin() + start + size
    );
}

// ============================================================
// Jacobsthal insertion order
// ============================================================

// pending[0] corresponds to b2.
// Example: b3, b2, b5, b4, ...
std::vector<std::size_t>PmergeMe::generateJacobsthalOrder(
    std::size_t count)
{
    std::vector<std::size_t> order;

    std::size_t previous = 1;
    std::size_t jacPrev = 1;
    std::size_t jacCur = 3;
    const std::size_t last = count + 1;

    while (previous < last)
    {
        const std::size_t end = std::min(jacCur, last);

        for (std::size_t i = end; i > previous; --i)
            order.push_back(i - 2);

        previous = end;

        if (previous == last)
            break;

        if (jacPrev > (last - jacCur) / 2)
        {
            jacCur = last;
        }
        else
        {
            const std::size_t next =
                jacCur + 2 * jacPrev;

            jacPrev = jacCur;
            jacCur = next;
        }
    }

    return order;
}

// ============================================================
// Ford-Johnson merge-insertion sort (Vector)
// ============================================================

void PmergeMe::fordJohnsonVector(
    std::vector<int> &data,
    std::size_t groupSize)
{
    const std::size_t groupCount = data.size() / groupSize;

    // debug
    std::cout << RED << "<<debug>> groupCount: "
              << groupCount << RESET << std::endl; 
    if (groupCount < 2)
        return;

    // --------------------------------------------------------
    // 1. Compare adjacent groups.
    //    Swap entire groups, not individual elements.
    // --------------------------------------------------------

    for (std::size_t p = 0; p + 1 < groupCount; p += 2)
    {
        const std::size_t left = p * groupSize;
        const std::size_t right = (p + 1) * groupSize;

        if (groupMax(data, left, groupSize) >
            groupMax(data, right, groupSize))
        {
            for (std::size_t k = 0; k < groupSize; ++k)
            {
                std::swap(
                    data[left + k],
                    data[right + k]
                );
            }
        }
    }

    // --------------------------------------------------------
    // 2. Recursively sort larger combined groups.
    // --------------------------------------------------------

    if (groupSize <= data.size() / 2)
        fordJohnsonVector(data, groupSize * 2);

    // --------------------------------------------------------
    // 3. Return from recursion.
    //    Build main chain and pending groups.
    // --------------------------------------------------------

    const std::size_t pairCount = groupCount / 2;
    const bool oddGroup = (groupCount % 2) != 0;

    const std::size_t completePrefix =
        groupCount * groupSize;

    // Store group indices, not copied groups.
    std::vector<std::size_t> chain;
    chain.reserve(groupCount);

    // b1 is always before a1.
    chain.push_back(0);

    // Add all a groups to the main chain.
    for (std::size_t i = 0; i < pairCount; ++i)
        chain.push_back(2 * i + 1);

    // Collect b2, b3, ... as pending.
    std::vector<std::size_t> pending;

    for (std::size_t i = 1; i < pairCount; ++i)
        pending.push_back(2 * i);

    // A complete unpaired group is also pending.
    if (oddGroup)
        pending.push_back(groupCount - 1);

    // --------------------------------------------------------
    // 4. Insert pending in Jacobsthal order.
    // --------------------------------------------------------

    const std::vector<std::size_t> order =
        generateJacobsthalOrder(pending.size());

    for (std::size_t j = 0; j < order.size(); ++j)
    {
        const std::size_t id = pending[order[j]];

        std::size_t limit = chain.size();

        // For b_i, search only before its paired a_i.
        // A straggler has no partner.
        if (!(oddGroup && id == groupCount - 1))
        {
            const std::size_t partner = id + 1;

            limit = 0;

            while (limit < chain.size() &&
                   chain[limit] != partner)
            {
                ++limit;
            }

            if (limit == chain.size())
                throw std::logic_error(
                    "lost pair association"
                );
        }

        // Binary search for insertion position.
        std::size_t lo = 0;
        std::size_t hi = limit;

        const int key =
            groupMax(data, id * groupSize, groupSize);

        while (lo < hi)
        {
            const std::size_t mid =
                lo + (hi - lo) / 2;

            const int middleValue = groupMax(
                data,
                chain[mid] * groupSize,
                groupSize
            );

            if (middleValue < key)
                lo = mid + 1;
            else
                hi = mid;
        }

        chain.insert(chain.begin() + lo, id);
    }

    // --------------------------------------------------------
    // 5. Rebuild data in sorted group order.
    // --------------------------------------------------------

    std::vector<int> merged;
    merged.reserve(data.size());

    for (std::size_t i = 0; i < chain.size(); ++i)
    {
        appendGroup(
            merged,
            data,
            chain[i] * groupSize,
            groupSize
        );
    }

    // Preserve incomplete trailing group elements.
    merged.insert(
        merged.end(),
        data.begin() + completePrefix,
        data.end()
    );

    data.swap(merged);
}

// ============================================================
// Run
// ============================================================

void PmergeMe::run(int argc, char **argv)
{
    if (argc < 2)
        throw std::runtime_error(
            "provide positive integers"
        );

    loadVector(argc, argv);
    loadDeque(argc, argv);

    std::cout << "Before:";

    for (std::size_t i = 0; i < _vector.size(); ++i)
        std::cout << " " << _vector[i];

    std::cout << std::endl;

    // ソート全体のCPU時間の計測
    // 計測開始
    const std::clock_t start = std::clock();

    fordJohnsonVector(_vector, 1);

    // 計測停止
    const std::clock_t end = std::clock();

    /* time in micro second 
    s  = 1 sec
    ms = 0.001sec(1/1,000)
    us = 0.000001sec(1/1000,000) 
    */
    const double elapsed =
        static_cast<double>(end - start)
        / CLOCKS_PER_SEC * 1000000.0;
    
    std::cout << "After: ";

    for (std::size_t i = 0; i < _vector.size(); ++i)
        std::cout << " " << _vector[i];

    std::cout << std::endl;

    std::cout << "Time to process a range of "
              << _vector.size()
              << " elements with std::vector : "
              << elapsed << " us"
              << std::endl;
}



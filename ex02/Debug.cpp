#include "Debug.hpp"
#include <iostream>
#include <vector>

static void printGroup(
    const std::vector<int> &data,
    std::size_t start,
    std::size_t groupSize)
{
    std::cout << "[";

    for (std::size_t k = 0; k < groupSize; ++k)
    {
        if (k != 0)
            std::cout << ", ";
        std::cout << data[start + k];
    }

    std::cout << "]";
}

void debugCompareGroups(
    const std::vector<int> &data,
    std::size_t left,
    std::size_t right,
    std::size_t groupSize,
    int leftMax,
    int rightMax)
{
    std::cout << "[COMPARE GROUPS]" << std::endl;

    std::cout << "left  group: ";
    printGroup(data, left, groupSize);
    std::cout << std::endl;

    std::cout << "right group: ";
    printGroup(data, right, groupSize);
    std::cout << std::endl;

    std::cout << "compare max: "
              << leftMax
              << (leftMax > rightMax ? " > " : " <= ")
              << rightMax
              << std::endl;

    std::cout << (leftMax > rightMax
        ? "[SWAP REQUIRED]"
        : "[NO SWAP]")
        << std::endl;
}

void debugSwappedGroups(
    const std::vector<int> &data,
    std::size_t left,
    std::size_t right,
    std::size_t groupSize)
{
    std::cout << "[AFTER GROUP SWAP]" << std::endl;

    std::cout << "left  group: ";
    printGroup(data, left, groupSize);
    std::cout << std::endl;

    std::cout << "right group: ";
    printGroup(data, right, groupSize);
    std::cout << std::endl;
}

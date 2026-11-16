#include "Debug.hpp"
#include <iostream>
#include <vector>

void printFordJohnsonStart(
    std::size_t groupSize,
    std::size_t groupCount)
{
    std::cout << "<<debug step1: make pair & swap>>"
              << std::endl;

    std::cout << "[ford-Johnson running..]" << std::endl;

    std::cout << "groupSize: "
              << groupSize << std::endl;

    std::cout << "groupCount: "
              << groupCount << std::endl;

    std::cout << "-------------------------" << std::endl;
}

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

void printMainPendingChain(
	const std::vector<int> &data,
    std::size_t groupSize,
    std::size_t groupCount,
    const std::vector<std::size_t> &chain,
    const std::vector<std::size_t> &pending,
    bool oddGroup)
{
    std::cout << "\n[RETURN FROM RECURSION..]"
              << std::endl;

    std::cout << "<<debug step2: create main/pending chain >>"
              << std::endl;

    std::cout << "groupSize: "
              << groupSize << std::endl;

    std::cout << "groupCount: "
              << groupCount << std::endl;

    std::cout << "---------------------" << std::endl;

    std::cout << "[MAIN CHAIN] ";
    for (std::size_t i = 0; i < chain.size(); ++i)
	{
		printGroupName(chain[i], groupCount, oddGroup);
		std::cout << "=";
		printGroupValues(data, chain[i], groupSize);
		std::cout << "  ";
	}
    std::cout << std::endl;

    std::cout << "[PENDING] ";
    for (std::size_t i = 0; i < pending.size(); ++i)
	{
		printGroupName(pending[i], groupCount, oddGroup);
    	std::cout << "=";
		printGroupValues(data, pending[i], groupSize);
		std::cout << "  ";
	}
    std::cout << std::endl;

    std::cout << "[ODD GROUP] "
              << (oddGroup ? "YES" : "NO")
              << std::endl;

    std::cout << "========================================"
              << std::endl;
}

#include "Debug.hpp"
#include <iostream>

void printJacobsthalOrder(
    const std::vector<int> &data,
    const std::vector<std::size_t> &pending,
    const std::vector<std::size_t> &order,
    std::size_t groupSize,
    std::size_t groupCount,
    bool oddGroup)
{
    std::cout << "\n========== STEP 3: JACOBSTHAL =========="
              << std::endl;

    std::cout << "[PENDING GROUPS] ";
    for (std::size_t i = 0; i < pending.size(); ++i)
    {
        const std::size_t id = pending[i];

        printGroupName(id, groupCount, oddGroup);
        std::cout << "=";
        printGroupValues(data, id, groupSize);
        std::cout << "  ";
    }
    std::cout << std::endl;

    std::cout << "[JACOBSTHAL ORDER] ";
    for (std::size_t i = 0; i < order.size(); ++i)
        std::cout << order[i] << " ";
    std::cout << std::endl;

    std::cout << "[ACTUAL INSERTION ORDER] ";
    for (std::size_t i = 0; i < order.size(); ++i)
    {
        const std::size_t id = pending[order[i]];

        printGroupName(id, groupCount, oddGroup);
        std::cout << "=";
        printGroupValues(data, id, groupSize);
        std::cout << "  ";
    }
    std::cout << std::endl;

    std::cout << "========================================"
              << std::endl;
}

// void printJacobsthalOrder(
//     const std::vector<std::size_t> &pending,
//     const std::vector<std::size_t> &order)
// {
//     std::cout << "\n========== STEP 3: JACOBSTHAL =========="
//               << std::endl;

//     std::cout << "[PENDING GROUP IDs] ";
//     for (std::size_t i = 0; i < pending.size(); ++i)
//         std::cout << pending[i] << " ";
//     std::cout << std::endl;

//     std::cout << "[JACOBSTHAL ORDER] ";
//     for (std::size_t i = 0; i < order.size(); ++i)
//         std::cout << order[i] << " ";
//     std::cout << std::endl;

//     std::cout << "[ACTUAL INSERTION ORDER] ";
//     for (std::size_t i = 0; i < order.size(); ++i)
//     {
//         std::cout << pending[order[i]] << " ";
//     }
//     std::cout << std::endl;

//     std::cout << "========================================"
//               << std::endl;
// }

void printGroupName(
    std::size_t id,
    std::size_t groupCount,
    bool oddGroup)
{
    if (oddGroup && id == groupCount - 1)
    {
        std::cout << "straggler";
    }
    else if (id % 2 == 0)
    {
        std::cout << "b" << (id / 2 + 1);
    }
    else
    {
        std::cout << "a" << (id / 2 + 1);
    }
}

void printGroupValues(
    const std::vector<int> &data,
    std::size_t id,
    std::size_t groupSize)
{
    const std::size_t start = id * groupSize;

    std::cout << "[";

    for (std::size_t i = 0; i < groupSize; ++i)
    {
        if (i > 0)
            std::cout << ", ";

        std::cout << data[start + i];
    }

    std::cout << "]";
}

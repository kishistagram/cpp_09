#include "Debug.hpp"
#include <iostream>

static void printGroups(
    const char *label,
    const std::vector<int> &data,
    const std::vector<std::size_t> &groups,
    std::size_t groupSize)
{
    std::cerr << label << std::endl;

    for (std::size_t i = 0; i < groups.size(); ++i)
    {
        const std::size_t id = groups[i];

        std::cerr << "group " << id << ": [";

        for (std::size_t k = 0; k < groupSize; ++k)
        {
            if (k != 0)
                std::cerr << ", ";

            std::cerr << data[id * groupSize + k];
        }

        std::cerr << "]" << std::endl;
    }
}

void debugGroups(
    const std::vector<int> &data,
    const std::vector<std::size_t> &chain,
    const std::vector<std::size_t> &pending,
    std::size_t groupSize)
{
    std::cerr << "\n[DEBUG] groupSize = "
              << groupSize << std::endl;

    printGroups("[MAIN CHAIN]", data, chain, groupSize);
    printGroups("[PENDING]", data, pending, groupSize);
}
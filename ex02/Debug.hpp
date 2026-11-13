#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <vector>
#include <cstddef>

void debugGroups(
    const std::vector<int> &data,
    const std::vector<std::size_t> &chain,
    const std::vector<std::size_t> &pending,
    std::size_t groupSize
);

#endif
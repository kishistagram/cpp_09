
#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <vector>
#include <cstddef>

void debugCompareGroups(
    const std::vector<int> &data,
    std::size_t left,
    std::size_t right,
    std::size_t groupSize,
    int leftMax,
    int rightMax);

void debugSwappedGroups(
    const std::vector<int> &data,
    std::size_t left,
    std::size_t right,
    std::size_t groupSize);

#endif



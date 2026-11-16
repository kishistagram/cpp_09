
#ifndef DEBUG_HPP
#define DEBUG_HPP

#include <vector>
#include <cstddef>

void printFordJohnsonStart(
    std::size_t groupSize,
    std::size_t groupCount);

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

// void printMainPendingChain(
// 	std::size_t groupSize,
// 	std::size_t groupCount,
// 	const std::vector<std::size_t> &chain,
// 	const std::vector<std::size_t> &pending,
// 	bool oddGroup);
void printMainPendingChain(
	const std::vector<int> &data,
	std::size_t groupSize,
	std::size_t groupCount,
	const std::vector<std::size_t> &chain,
	const std::vector<std::size_t> &pending,
	bool oddGroup);

// void printJacobsthalOrder(
// 	const std::vector<std::size_t> &pending,
// 	const std::vector<std::size_t> &order);

void printJacobsthalOrder(
    const std::vector<int> &data,
    const std::vector<std::size_t> &pending,
    const std::vector<std::size_t> &order,
    std::size_t groupSize,
    std::size_t groupCount,
    bool oddGroup);

void printGroupName(
    std::size_t id,
    std::size_t groupCount,
    bool oddGroup);

void printGroupValues(
    const std::vector<int> &data,
    std::size_t id,
    std::size_t groupSize);

#endif



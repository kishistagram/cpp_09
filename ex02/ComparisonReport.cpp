/* This is for  debugging */
#include "ComparisonReport.hpp"
#include <iostream>

ComparisonReport::ComparisonReport()
    : elementCount(0),
      pairComparisons(0),
      recursiveComparisons(0),
      pendingComparisons(0),
      totalComparisons(0)
{
}

ComparisonReport::ComparisonReport(std::size_t count)
    : elementCount(count),
      pairComparisons(0),
      recursiveComparisons(0),
      pendingComparisons(0),
      totalComparisons(0)
{
}

ComparisonReport::ComparisonReport(
    const ComparisonReport& other)
    : elementCount(other.elementCount),
      pairComparisons(other.pairComparisons),
      recursiveComparisons(other.recursiveComparisons),
      pendingComparisons(other.pendingComparisons),
      totalComparisons(other.totalComparisons)
{
}

ComparisonReport::~ComparisonReport()
{
}

ComparisonReport& ComparisonReport::operator=(
    const ComparisonReport& other)
{
    if (this != &other)
    {
        elementCount = other.elementCount;
        pairComparisons = other.pairComparisons;
        recursiveComparisons = other.recursiveComparisons;
        pendingComparisons = other.pendingComparisons;
        totalComparisons = other.totalComparisons;
    }

    return *this;
}

void ComparisonReport::calculateTotal(void)
{
    totalComparisons =
        pairComparisons
        + recursiveComparisons
        + pendingComparisons;
}

bool ComparisonReport::hasSameBreakdown(
    const ComparisonReport& other) const
{
    return elementCount == other.elementCount
        && pairComparisons == other.pairComparisons
        && recursiveComparisons
            == other.recursiveComparisons
        && pendingComparisons
            == other.pendingComparisons
        && totalComparisons
            == other.totalComparisons;
}

void printComparisonReport(
    const char* containerName,
    const ComparisonReport& report)
{
    std::cerr
        << "["
        << containerName
        << "][n="
        << report.elementCount
        << "]"
        << std::endl;

    std::cerr
        << "  pair      : "
        << report.pairComparisons
        << std::endl;

    std::cerr
        << "  recursive : "
        << report.recursiveComparisons
        << std::endl;

    std::cerr
        << "  pending   : "
        << report.pendingComparisons
        << std::endl;

    std::cerr
        << "  total     : "
        << report.totalComparisons
        << std::endl;

    std::cerr
        << "  formula   : "
        << report.pairComparisons
        << " + "
        << report.recursiveComparisons
        << " + "
        << report.pendingComparisons
        << " = "
        << report.totalComparisons
        << std::endl;
}


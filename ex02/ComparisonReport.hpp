#ifndef COMPARISON_REPORT_HPP
#define COMPARISON_REPORT_HPP

#include <cstddef>

struct ComparisonReport
{
	std::size_t elementCount;
	std::size_t pairComparisons;
	std::size_t recursiveComparisons;
	std::size_t pendingComparisons;
	std::size_t totalComparisons;

	ComparisonReport();
	explicit ComparisonReport(std::size_t count);
	ComparisonReport(const ComparisonReport &other);
	~ComparisonReport();
	ComparisonReport &operator=(const ComparisonReport &other);

	void calculateTotal(void);
	bool hasSameBreakdown(const ComparisonReport &other) const;

};

void printComparisonReport(
	const char &containerName,
	const ComparisonReport &report);


#endif

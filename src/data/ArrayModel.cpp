#include "ArrayModel.hpp"

#include <algorithm>
#include <random>

using namespace std;

ArrayModel::ArrayModel()
    : comparisons(0),
      swaps(0),
      activeIndex1(-1),
      activeIndex2(-1)
{
    sortedStart = -1;
    sortedEnd = -1;
}

void ArrayModel::generate(int n)
{
    values.clear();
    values.reserve(n);

    for (int i = 1; i <= n; ++i)
    {
        values.push_back(i);
    }

    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(values.begin(), values.end(), gen);

    originalValues = values;

    resetCounters();
    clearActiveIndices();
    clearSortedRange();
    
}

void ArrayModel::resetCounters()
{
    comparisons = 0;
    swaps = 0;
}

void ArrayModel::swap(int i, int j)
{
    if (i >= 0 && j >= 0 && i < size() && j < size())
    {
        std::swap(values[i], values[j]);
        swaps++;
    }
}

void ArrayModel::incrementComparison()
{
    comparisons++;
}

void ArrayModel::setActiveIndices(int index1, int index2)
{
    activeIndex1 = index1;
    activeIndex2 = index2;
}

void ArrayModel::clearActiveIndices()
{
    activeIndex1 = -1;
    activeIndex2 = -1;
}

const std::vector<int> &ArrayModel::getValues() const
{
    return values;
}

int ArrayModel::getComparisons() const
{
    return comparisons;
}

int ArrayModel::getSwaps() const
{
    return swaps;
}

int ArrayModel::getActiveIndex1() const
{
    return activeIndex1;
}

int ArrayModel::getActiveIndex2() const
{
    return activeIndex2;
}

int ArrayModel::size() const
{
    return static_cast<int>(values.size());
}

void ArrayModel::restoreOriginal()
{
    values = originalValues;
    resetCounters();
    clearActiveIndices();
}

void ArrayModel::setSortedRange(int start, int end)
{
    sortedStart = start;
    sortedEnd   = end;
}

int ArrayModel::getSortedStart() const
{
    return sortedStart;
}

int ArrayModel::getSortedEnd() const
{
    return sortedEnd;
}

void ArrayModel::clearSortedRange()
{
    sortedStart = -1;
    sortedEnd   = -1;
}

void ArrayModel::setValue(int index, int value)
{
    values[index] = value;
}
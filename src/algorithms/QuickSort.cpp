#include "QuickSort.hpp"
#include "../data/ArrayModel.hpp"

QuickSort::QuickSort()
    : partitioning(false), finished(false), initialized(false)
{
}

void QuickSort::step(ArrayModel& model)
{
    if (finished)
        return;

    int n = model.size();

    // Initialize only once
    if (!initialized)
    {
        ranges.push({0, n - 1});
        initialized = true;
    }

    // If not currently partitioning → get next range
    if (!partitioning)
    {
        if (ranges.empty())
        {
            finished = true;
            model.setSortedRange(0, n - 1);
            model.clearActiveIndices();
            return;
        }

        auto range = ranges.top();
        ranges.pop();

        low = range.first;
        high = range.second;

        if (low >= high)
            return;

        pivotIndex = high;
        i = low - 1;
        j = low;

        partitioning = true;
        return;
    }

    const auto& values = model.getValues();

    if (j < high)
    {
        model.setActiveIndices(j, pivotIndex);
        model.incrementComparison();

        if (values[j] < values[pivotIndex])
        {
            i++;
            model.swap(i, j);
        }

        j++;
    }
    else
    {
        model.swap(i + 1, high);
        int newPivot = i + 1;

        // Push right
        if (newPivot + 1 < high)
            ranges.push({newPivot + 1, high});

        // Push left
        if (low < newPivot - 1)
            ranges.push({low, newPivot - 1});

        partitioning = false;
    }
}

bool QuickSort::isFinished() const
{
    return finished;
}

std::string QuickSort::getName() const
{
    return "Quick Sort";
}
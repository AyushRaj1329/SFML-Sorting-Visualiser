#include "InsertionSort.hpp"
#include "../data/ArrayModel.hpp"

InsertionSort::InsertionSort()
    : i(1), j(1), finished(false)
{
}

void InsertionSort::step(ArrayModel& model)
{
    if (finished)
        return;

    int n = model.size();

    if (i >= n)
    {
        finished = true;
        model.setSortedRange(0, n - 1);
        model.clearActiveIndices();
        return;
    }

    const auto& values = model.getValues();

    if (j > 0)
    {
        model.setActiveIndices(j, j - 1);
        model.incrementComparison();

        if (values[j] < values[j - 1])
        {
            model.swap(j, j - 1);
            j--;
            return;  // Stay in same i
        }
    }

    // Current element inserted correctly
    model.setSortedRange(0, i);   // everything up to i sorted
    i++;
    j = i;
}

bool InsertionSort::isFinished() const
{
    return finished;
}

std::string InsertionSort::getName() const
{
    return "Insertion Sort";
}
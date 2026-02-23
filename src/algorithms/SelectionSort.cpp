#include "SelectionSort.hpp"
#include "../data/ArrayModel.hpp"

SelectionSort::SelectionSort()
    : i(0), j(1), minIndex(0), finished(false)
{
}

void SelectionSort::step(ArrayModel &model)
{
    if (finished)
        return;

    int n = model.size();

    if (i >= n - 1)
    {
        finished = true;
        model.setSortedRange(0, n - 1);
        model.clearActiveIndices();
        return;
    }

    const auto &values = model.getValues();

    if (j < n)
    {
        model.setActiveIndices(j, minIndex);
        model.incrementComparison();

        if (values[j] < values[minIndex])
            minIndex = j;

        j++;
    }
    else
    {
        model.swap(i, minIndex);

        model.setSortedRange(0, i);  // left portion sorted

        i++;
        minIndex = i;
        j = i + 1;
    }
}

bool SelectionSort::isFinished() const
{
    return finished;
}

std::string SelectionSort::getName() const
{
    return "Selection Sort";
}
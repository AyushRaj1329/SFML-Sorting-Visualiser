#include "SelectionSort.hpp"
#include "../data/ArrayModel.hpp"

SelectionSort::SelectionSort()
    : i(0), j(1), minIndex(0)
{
}

void SelectionSort::step(ArrayModel& model)
{
    int n = model.size();

    if (i >= n - 1)
        return;

    const auto& values = model.getValues();

    model.setActiveIndices(j, minIndex);
    model.incrementComparison();

    if (values[j] < values[minIndex])
        minIndex = j;

    j++;

    if (j >= n)
    {
        model.swap(i, minIndex);  // swap() already increments swaps

        i++;
        minIndex = i;
        j = i + 1;
    }
}

bool SelectionSort::isFinished() const
{
    return false;
}

std::string SelectionSort::getName() const
{
    return "Selection Sort";
}
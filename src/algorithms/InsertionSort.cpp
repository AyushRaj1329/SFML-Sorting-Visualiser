#include "InsertionSort.hpp"
#include "../data/ArrayModel.hpp"

InsertionSort::InsertionSort()
    : i(1), j(1)
{
}

void InsertionSort::step(ArrayModel& model)
{
    int n = model.size();

    if (i >= n)
        return;

    const auto& values = model.getValues();

    if (j > 0)
    {
        model.setActiveIndices(j, j - 1);
        model.incrementComparison();

        if (values[j] < values[j - 1])
        {
            model.swap(j, j - 1);
            j--;
            return;   // stay on same i
        }
    }

    // Move to next element
    i++;
    j = i;
}

bool InsertionSort::isFinished() const
{
    return false;
}

std::string InsertionSort::getName() const
{
    return "Insertion Sort";
}
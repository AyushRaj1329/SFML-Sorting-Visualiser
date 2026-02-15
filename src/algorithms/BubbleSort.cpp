#include "BubbleSort.hpp"

BubbleSort::BubbleSort()
    : i(0), j(0), finished(false)
{
}

void BubbleSort::step(ArrayModel& model)
{
    if (finished)
        return;

    int n = model.size();

    if (i >= n - 1)
    {
        finished = true;
        model.clearActiveIndices();
        return;
    }

    if (j < n - i - 1)
    {
        model.setActiveIndices(j, j + 1);
        model.incrementComparison();

        if (model.getValues()[j] > model.getValues()[j + 1])
        {
            model.swap(j, j + 1);
        }

        j++;
    }
    else
    {
        j = 0;
        i++;
    }
}

bool BubbleSort::isFinished() const
{
    return finished;
}

std::string BubbleSort::getName() const
{
    return "Bubble Sort";
}

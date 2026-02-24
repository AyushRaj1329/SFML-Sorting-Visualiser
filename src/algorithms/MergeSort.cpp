#include "MergeSort.hpp"
#include "../data/ArrayModel.hpp"
#include <algorithm>

MergeSort::MergeSort()
    : currentSize(1),
      leftStart(0),
      merging(false),
      finished(false),
      newPass(true)
{
}

void MergeSort::step(ArrayModel& model)
{
    if (finished)
        return;

    int n = model.size();

    if (currentSize >= n)
    {
        finished = true;
        model.setSortedRange(0, n - 1);
        model.clearActiveIndices();
        return;
    }

    if (newPass)
    {
        temp = model.getValues();   // copy ONCE per pass
        newPass = false;
    }

    if (!merging)
    {
        if (leftStart >= n - 1)
        {
            currentSize *= 2;
            leftStart = 0;
            newPass = true;   // start new merge pass
            return;
        }

        mid = std::min(leftStart + currentSize - 1, n - 1);
        rightEnd = std::min(leftStart + 2 * currentSize - 1, n - 1);

        i = leftStart;
        j = mid + 1;
        k = leftStart;

        merging = true;
        return;
    }

    if (i <= mid && j <= rightEnd)
    {
        model.setActiveIndices(i, j);
        model.incrementComparison();

        if (temp[i] <= temp[j])
        {
            model.setValue(k++, temp[i++]);
        }
        else
        {
            model.setValue(k++, temp[j++]);
        }
    }
    else if (i <= mid)
    {
        model.setValue(k++, temp[i++]);
    }
    else if (j <= rightEnd)
    {
        model.setValue(k++, temp[j++]);
    }
    else
    {
        leftStart += 2 * currentSize;
        merging = false;
    }
}

bool MergeSort::isFinished() const
{
    return finished;
}

std::string MergeSort::getName() const
{
    return "Merge Sort";
}
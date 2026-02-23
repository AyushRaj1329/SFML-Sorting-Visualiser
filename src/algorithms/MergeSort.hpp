#pragma once

#include "SortingAlgorithm.hpp"
#include <vector>

class MergeSort : public SortingAlgorithm
{
public:
    MergeSort();

    void step(ArrayModel& model) override;
    bool isFinished() const override;
    std::string getName() const override;

private:
    int currentSize;
    int leftStart;

    int mid;
    int rightEnd;

    int i, j, k;

    std::vector<int> temp;

    bool merging;
    bool finished;
};
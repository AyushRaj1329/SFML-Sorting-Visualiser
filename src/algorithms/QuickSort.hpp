#pragma once

#include "SortingAlgorithm.hpp"
#include <stack>

class QuickSort : public SortingAlgorithm
{
public:
    QuickSort();

    void step(ArrayModel& model) override;
    bool isFinished() const override;
    std::string getName() const override;

private:
    std::stack<std::pair<int,int>> ranges;

    int low;
    int high;
    int pivotIndex;
    int i;
    int j;

    bool partitioning;
    bool finished;
    bool initialized;
};
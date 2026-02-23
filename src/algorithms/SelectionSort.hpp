#pragma once

#include "SortingAlgorithm.hpp"

class SelectionSort : public SortingAlgorithm
{
public:
    SelectionSort();

    void step(ArrayModel& model) override;
    bool isFinished() const override;
    std::string getName() const override;

private:
    int i;
    int j;
    int minIndex;
};
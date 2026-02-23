#pragma once

#include "SortingAlgorithm.hpp"

class InsertionSort : public SortingAlgorithm
{
public:
    InsertionSort();

    void step(ArrayModel& model) override;
    bool isFinished() const override;
    std::string getName() const override;


private:
    int i;
    int j;
    bool finished; 
};
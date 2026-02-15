#pragma once

#include "SortingAlgorithm.hpp"
using namespace std;

class BubbleSort : public SortingAlgorithm
{
public:
    BubbleSort();

    void step(ArrayModel& model) override;
    bool isFinished() const override;
    string getName() const override;

private:
    int i;
    int j;
    bool finished;
};

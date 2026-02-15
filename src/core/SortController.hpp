#pragma once

#include "../algorithms/SortingAlgorithm.hpp"
#include "../algorithms/BubbleSort.hpp"

class SortController
{
public:
    SortController();

    void start(ArrayModel& model);
    void update(ArrayModel& model);

    void pause();
    void resume();
    void restart(ArrayModel& model);

    bool isRunning() const;
    bool isFinished() const;

private:
    SortingAlgorithm* algorithm;
    bool running;
};

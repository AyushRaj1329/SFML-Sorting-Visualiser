#include "SortController.hpp"

SortController::SortController()
    : algorithm(nullptr), running(false)
{
}

void SortController::start(ArrayModel& model)
{
    delete algorithm;  // clean old one
    algorithm = new BubbleSort();

    running = true;
}

void SortController::update(ArrayModel& model)
{
    if (!running || !algorithm)
        return;

    if (!algorithm->isFinished())
    {
        algorithm->step(model);
    }
    else
    {
        running = false;
    }
}

void SortController::pause()
{
    running = false;
}

void SortController::resume()
{
    if (algorithm && !algorithm->isFinished())
        running = true;
}

void SortController::restart(ArrayModel& model)
{
    delete algorithm;
    algorithm = new BubbleSort();

    running = true;
}

bool SortController::isRunning() const
{
    return running;
}

bool SortController::isFinished() const
{
    return algorithm && algorithm->isFinished();
}

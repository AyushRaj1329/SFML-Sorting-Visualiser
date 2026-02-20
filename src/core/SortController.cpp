#include "SortController.hpp"

SortController::SortController()
    : algorithm(nullptr), running(false), speedMultiplier(1.0f), accumulatedTime(0.0f), baseStepTime(0.02f)
{
}

void SortController::start(ArrayModel &model)
{
    delete algorithm; // clean old one
    algorithm = new BubbleSort();

    running = true;

    accumulatedTime = 0.0f;
    clock.restart();
}

// void SortController::update(ArrayModel& model)
// {
//     if (!running || !algorithm)
//         return;

//     if (!algorithm->isFinished())
//     {
//         algorithm->step(model);
//     }
//     else
//     {
//         running = false;
//     }
// }

// void SortController::update(ArrayModel &model)
// {
//     if (!running || !algorithm)
//         return;

//     for (int i = 0; i < stepsPerFrame; ++i)
//     {
//         if (!algorithm->isFinished())
//         {
//             algorithm->step(model);
//         }
//         else
//         {
//             running = false;
//             break;
//         }
//     }
// }

void SortController::update(ArrayModel &model)
{
    if (!running || !algorithm)
        return;

    float deltaTime = clock.restart().asSeconds();
    accumulatedTime += deltaTime;

    float adjustedStepTime = baseStepTime / speedMultiplier;

    while (accumulatedTime >= adjustedStepTime)
    {
        if (!algorithm->isFinished())
        {
            algorithm->step(model);
            accumulatedTime -= adjustedStepTime;
        }
        else
        {
            running = false;
            break;
        }
    }
}

void SortController::pause()
{
    running = false;
    accumulatedTime = 0.0f;
    clock.restart();
}

void SortController::resume()
{
    if (algorithm && !algorithm->isFinished())
    {
        running = true;
        accumulatedTime = 0.0f;
        clock.restart();
    }
}

void SortController::restart(ArrayModel &model)
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

void SortController::increaseSpeed()
{
    if (speedMultiplier < 5.0f)
        speedMultiplier += 0.25f;
}

void SortController::decreaseSpeed()
{
    if (speedMultiplier > 0.25f)
        speedMultiplier -= 0.25f;
}

float SortController::getSpeedMultiplier() const
{
    return speedMultiplier;
}
#include "SortController.hpp"
#include "../algorithms/BubbleSort.hpp"
#include "../algorithms/SelectionSort.hpp"
#include "../algorithms/InsertionSort.hpp"
#include "../algorithms/QuickSort.hpp"
#include "../algorithms/MergeSort.hpp"
#include "../data/ArrayModel.hpp"

SortController::SortController()
    : algorithm(nullptr),
      running(false),
      currentAlgorithm(AlgorithmType::Bubble),
      speedMultiplier(1.0f),
      accumulatedTime(0.0f),
      baseStepTime(0.02f)
{
}

void SortController::start(ArrayModel &model, AlgorithmType type)
{
    delete algorithm;
    currentAlgorithm = type;

    switch (type)
    {
    case AlgorithmType::Bubble:
        algorithm = new BubbleSort();
        break;

    case AlgorithmType::Selection:
        algorithm = new SelectionSort();
        break;

    case AlgorithmType::Insertion:
        algorithm = new InsertionSort();
        break;
        
    case AlgorithmType::Quick:
        algorithm = new QuickSort();
        break;

    case AlgorithmType::Merge:
        algorithm = new MergeSort();
        break;
    }

    running = true;

    accumulatedTime = 0.0f;
    clock.restart();
}

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
    if (!algorithm)
        return;

    // Store algorithm type
    AlgorithmType type = currentAlgorithm;

    // Delete safely
    delete algorithm;
    algorithm = nullptr;

    // Recreate algorithm fresh
    switch (type)
    {
    case AlgorithmType::Bubble:
        algorithm = new BubbleSort();
        break;

    case AlgorithmType::Selection:
        algorithm = new SelectionSort();
        break;

    case AlgorithmType::Insertion:
        algorithm = new InsertionSort();
        break;

    case AlgorithmType::Quick:
        algorithm = new QuickSort();
        break;

    case AlgorithmType::Merge:
        algorithm = new MergeSort();
        break;
    }

    // Reset timing system
    accumulatedTime = 0.0f;
    clock.restart();

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

AlgorithmType SortController::getCurrentAlgorithmType() const
{
    return currentAlgorithm;
}

void SortController::reset()
{
    delete algorithm;
    algorithm = nullptr;

    running = false;

    speedMultiplier = 1.0f;
    accumulatedTime = 0.0f;

    clock.restart();
}
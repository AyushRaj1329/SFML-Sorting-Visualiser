#pragma once
#include <SFML/System.hpp>

#include "../algorithms/SortingAlgorithm.hpp"
#include "../algorithms/AlgorithmType.hpp"


class ArrayModel;

class SortController
{
public:
    SortController();

    void start(ArrayModel& model, AlgorithmType type);
    void update(ArrayModel &model);

    void pause();
    void resume();
    void restart(ArrayModel &model);
    void reset();
    

    bool isRunning() const;
    bool isFinished() const;

    void increaseSpeed();
    void decreaseSpeed();

    float getSpeedMultiplier() const;
    AlgorithmType getCurrentAlgorithmType() const;

private:
    SortingAlgorithm *algorithm;
    bool running;
    AlgorithmType currentAlgorithm;
    float speedMultiplier; // 1.0 = normal
    sf::Clock clock;       // measures frame time
    float accumulatedTime; // time buffer
    float baseStepTime;    // base time per step
};

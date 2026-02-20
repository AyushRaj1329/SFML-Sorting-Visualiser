#pragma once
#include <SFML/System.hpp>


#include "../algorithms/SortingAlgorithm.hpp"
#include "../algorithms/BubbleSort.hpp"


class SortController
{
public:
    SortController();

    void start(ArrayModel &model);
    void update(ArrayModel &model);

    void pause();
    void resume();
    void restart(ArrayModel &model);

    bool isRunning() const;
    bool isFinished() const;

    void increaseSpeed();
    void decreaseSpeed();

    float getSpeedMultiplier() const;

private:
    SortingAlgorithm *algorithm;
    bool running;
    float speedMultiplier; // 1.0 = normal
    sf::Clock clock;       // measures frame time
    float accumulatedTime; // time buffer
    float baseStepTime;    // base time per step
};

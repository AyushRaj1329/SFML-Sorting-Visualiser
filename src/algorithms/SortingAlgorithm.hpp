#pragma once

#include "../data/ArrayModel.hpp"
#include <string>

class SortingAlgorithm
{
public:
    virtual ~SortingAlgorithm() = default;

    // One step of sorting
    virtual void step(ArrayModel& model) = 0;

    // Is sorting complete?
    virtual bool isFinished() const = 0;

    // Algorithm name
    virtual std::string getName() const = 0;
};
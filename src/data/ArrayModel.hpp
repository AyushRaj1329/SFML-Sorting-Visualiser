#pragma once

#include <vector>

class ArrayModel
{
public:
    ArrayModel();

    // Generate values from 1 to n and shuffle them
    void generate(int n);

    // Reset comparison and swap counters
    void resetCounters();

    // Swap two elements and increment swap counter
    void swap(int i, int j);

    // Increment comparison counter
    void incrementComparison();

    // Set active indices (for highlighting in rendering)
    void setActiveIndices(int index1, int index2);

    // Clear active indices
    void clearActiveIndices();

    // Restore the original shuffled array
    void restoreOriginal();


    // Getters
    const std::vector<int>& getValues() const;
    int getComparisons() const;
    int getSwaps() const;
    int getActiveIndex1() const;
    int getActiveIndex2() const;
    int size() const;

private:
    std::vector<int> values;
    std::vector<int> originalValues;

    int comparisons;
    int swaps;

    int activeIndex1;
    int activeIndex2;

};

#include "UIOverlay.hpp"
#include <iostream>
#include <sstream>
#include <iomanip>

UIOverlay::UIOverlay()
    : infoText(font) // 🔥 Construct text with font
{
    if (!font.openFromFile("assets/fonts/roboto.ttf"))
    {
        std::cerr << "Failed to load font\n";
    }
    infoText.setCharacterSize(18);
    infoText.setFillColor(sf::Color::Black);
    infoText.setPosition({10.f, 10.f});
}

void UIOverlay::update(const ArrayModel &model,
                       const SortController &controller,
                       VisualizerState state)
{
    std::stringstream ss;

    // Algorithm Name
    ss << "Algorithm: ";

    switch (controller.getCurrentAlgorithmType())
    {
    case AlgorithmType::Bubble:
        ss << "Bubble Sort";
        break;
    case AlgorithmType::Selection:
        ss << "Selection Sort";
        break;
    case AlgorithmType::Insertion:
        ss << "Insertion Sort";
        break;
    }

    ss << "\n";

    // State
    ss << "State: ";
    switch (state)
    {
    case VisualizerState::WaitingForInput:
        ss << "Waiting For Input";
        break;
    case VisualizerState::Ready:
        ss << "Ready";
        break;
    case VisualizerState::Sorting:
        ss << "Sorting";
        break;
    case VisualizerState::Paused:
        ss << "Paused";
        break;
    case VisualizerState::Finished:
        ss << "Finished";
        break;
    }
    ss << "\n";

    // Speed
    ss << "Speed: "
       << std::fixed << std::setprecision(2)
       << controller.getSpeedMultiplier()
       << "x\n";

    // Comparisons
    ss << "Comparisons: " << model.getComparisons() << "\n";

    // Swaps
    ss << "Swaps: " << model.getSwaps();

    infoText.setString(ss.str());
}

void UIOverlay::draw(sf::RenderWindow &window)
{
    window.draw(infoText);
}
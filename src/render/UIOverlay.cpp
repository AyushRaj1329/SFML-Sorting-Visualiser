#include "UIOverlay.hpp"
#include <iostream>
#include <sstream>

UIOverlay::UIOverlay()
    : infoText(font),
      controlsText(font)
{
    if (!font.openFromFile("assets/fonts/roboto.ttf"))
    {
        std::cerr << "Failed to load font\n";
    }

    // 🔹 Bottom panel settings
    float panelHeight = 150.f;

    // backgroundPanel.setSize({800.f, panelHeight});
    backgroundPanel.setFillColor(sf::Color(230, 230, 230));
    // backgroundPanel.setPosition({0.f, 600.f - panelHeight});

    // 🔹 Vertical divider
    dividerLine.setSize({2.f, panelHeight});
    dividerLine.setFillColor(sf::Color(180, 180, 180));
    // dividerLine.setPosition({400.f, 600.f - panelHeight});

    // 🔹 Left section text (Sorting Info)
    infoText.setCharacterSize(14);
    infoText.setFillColor(sf::Color::Black);
    // infoText.setPosition({20.f, 600.f - panelHeight + 10.f});

    // 🔹 Right section text (Controls)
    controlsText.setCharacterSize(14);
    controlsText.setFillColor(sf::Color::Black);
    // controlsText.setPosition({420.f, 600.f - panelHeight + 10.f});
}

void UIOverlay::update(const ArrayModel &model,
                       const SortController &controller,
                       VisualizerState state,
                       AlgorithmType selectedAlgorithm,
                       int elementCount)
{
    std::stringstream left;
    std::stringstream right;

    // ---------- Determine Algorithm ----------
    AlgorithmType displayAlgo;

    if (state == VisualizerState::Sorting ||
        state == VisualizerState::Paused ||
        state == VisualizerState::Finished)
    {
        displayAlgo = controller.getCurrentAlgorithmType();
    }
    else
    {
        displayAlgo = selectedAlgorithm;
    }

    std::string algoName;
    std::string complexity;

    switch (displayAlgo)
    {
    case AlgorithmType::Bubble:
        algoName = "Bubble Sort";
        complexity = "O(n^2)";
        break;

    case AlgorithmType::Selection:
        algoName = "Selection Sort";
        complexity = "O(n^2)";
        break;

    case AlgorithmType::Insertion:
        algoName = "Insertion Sort";
        complexity = "O(n^2)";
        break;
        
    case AlgorithmType::Quick:
        algoName = "Quick Sort";
        complexity = "O(n log n)";
        break;

    case AlgorithmType::Merge:
        algoName = "Merge Sort";
        complexity = "O(n log n)";
        break;
    }

    // ---------- State Text ----------
    std::string stateText;

    switch (state)
    {
    case VisualizerState::WaitingForInput:
        stateText = "Waiting";
        break;
    case VisualizerState::Ready:
        stateText = "Ready";
        break;
    case VisualizerState::Sorting:
        stateText = "Sorting";
        break;
    case VisualizerState::Paused:
        stateText = "Paused";
        break;
    case VisualizerState::Finished:
        stateText = "Finished";
        break;
    }

    // 🔹 Change background color based on state
    switch (state)
    {
    case VisualizerState::WaitingForInput:
        backgroundPanel.setFillColor(sf::Color(120, 170, 255));
        break;

    case VisualizerState::Ready:
        backgroundPanel.setFillColor(sf::Color(80, 200, 255));
        break;

    case VisualizerState::Sorting:
        backgroundPanel.setFillColor(sf::Color(120, 220, 120));
        break;

    case VisualizerState::Paused:
        backgroundPanel.setFillColor(sf::Color(255, 170, 90));
        break;

    case VisualizerState::Finished:
        backgroundPanel.setFillColor(sf::Color(70, 200, 120));
        break;
    }

    // ---------- LEFT SECTION (Sorting Info) ----------
    left << "SORTING INFO\n";
    left << "----------------------------\n";
    left << "Algorithm        : " << algoName << "\n";
    left << "Complexity     : " << complexity << "\n";
    left << "State                : " << stateText << "\n";
    left << "Elements        : " << elementCount << "\n";
    left << "Speed             : x" << controller.getSpeedMultiplier() << "\n";
    left << "Comparisons : " << model.getComparisons() << "\n";
    left << "Swaps             : " << model.getSwaps() << "\n";

    // ---------- RIGHT SECTION (Controls) ----------
    right << "KEYBOARD CONTROLS\n";
    right << "----------------------------\n";
    right << "Enter       - Generate / Start\n";
    right << "Space       - Pause / Resume\n";
    right << "R           - Restart\n";
    right << "Shift + R   - Reset\n";
    right << "1 / 2 / 3 / 4 / 5  - Select Algorithm\n";
    right << "+ / -       - Element Count\n";
    right << "> / <       - Speed Control\n";

    infoText.setString(left.str());
    controlsText.setString(right.str());
}

// void UIOverlay::draw(sf::RenderWindow &window)
// {
//     window.draw(backgroundPanel);
//     window.draw(dividerLine);
//     window.draw(infoText);
//     window.draw(controlsText);
// }

void UIOverlay::draw(sf::RenderWindow &window)
{
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    float panelHeight = windowHeight * 0.25f; // 25% of window height
    float panelTop = windowHeight - panelHeight;

    // 🔹 Dynamic font scaling
    unsigned int dynamicSize = static_cast<unsigned int>(windowHeight * 0.022f);

    // Clamp range
    if (dynamicSize < 12)
        dynamicSize = 12;
    if (dynamicSize > 22)
        dynamicSize = 22;

    infoText.setCharacterSize(dynamicSize);
    controlsText.setCharacterSize(dynamicSize);

    // 🔹 Background Panel
    backgroundPanel.setSize({windowWidth, panelHeight});
    backgroundPanel.setPosition({0.f, panelTop});

    // 🔹 Divider Line (centered)
    dividerLine.setSize({2.f, panelHeight});
    dividerLine.setPosition({windowWidth / 2.f, panelTop});

    // 🔹 Left Text Position
    infoText.setPosition({20.f, panelTop + 10.f});

    // 🔹 Right Text Position
    controlsText.setPosition({windowWidth / 2.f + 20.f, panelTop + 10.f});

    window.draw(backgroundPanel);
    window.draw(dividerLine);
    window.draw(infoText);
    window.draw(controlsText);
}
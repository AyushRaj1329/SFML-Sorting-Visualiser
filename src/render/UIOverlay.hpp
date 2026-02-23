#pragma once

#include <SFML/Graphics.hpp>

#include "../data/ArrayModel.hpp"
#include "../core/SortController.hpp"
#include "../core/VisualizerState.hpp"
#include "../algorithms/AlgorithmType.hpp"

class UIOverlay
{
public:
    UIOverlay();

    void update(const ArrayModel &model,
                const SortController &controller,
                VisualizerState state,
                AlgorithmType selectedAlgorithm,
                int elementCount);

    void draw(sf::RenderWindow &window);

private:
    sf::Font font;

    // 🔹 Bottom background panel
    sf::RectangleShape backgroundPanel;

    // 🔹 Vertical divider line
    sf::RectangleShape dividerLine;

    // 🔹 Left section text (Sorting Info)
    sf::Text infoText;

    // 🔹 Right section text (Keyboard Controls)
    sf::Text controlsText;
};
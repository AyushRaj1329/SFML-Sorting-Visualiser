#pragma once

#include <SFML/Graphics.hpp>

#include "../data/ArrayModel.hpp"
#include "../core/SortController.hpp"
#include "../core/VisualizerState.hpp"


class UIOverlay
{
public:
    UIOverlay();
    float getSpeedMultiplier() const;

    void update(const ArrayModel& model,
                const SortController& controller,
                VisualizerState state);

    void draw(sf::RenderWindow& window);


private:
    sf::Font font;
    sf::Text infoText;
};

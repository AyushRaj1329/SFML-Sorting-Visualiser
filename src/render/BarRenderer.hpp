#pragma once

#include <SFML/Graphics.hpp>
#include "../data/ArrayModel.hpp"

class BarRenderer
{
public:
    BarRenderer();

    void draw(sf::RenderWindow& window, const ArrayModel& model);

private:
    sf::Color normalColor;
    sf::Color activeColor;
};

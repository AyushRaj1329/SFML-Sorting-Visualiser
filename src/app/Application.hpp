#pragma once

#include <SFML/Graphics.hpp>

class Application
{
public:
    Application();
    void run();

private:
    void processEvents();
    void update();
    void render();

    sf::RenderWindow window;
};
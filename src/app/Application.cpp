#include "Application.hpp"

Application::Application()
    : window(sf::VideoMode({800, 600}), "Sorting Visualizer")
{
    window.setFramerateLimit(60);
}

void Application::run()
{
    while (window.isOpen())
    {
        processEvents();
        update();
        render();
    }
}

void Application::processEvents()
{
    while (auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (event->is<sf::Event::KeyPressed>())
        {
            if (event->getIf<sf::Event::KeyPressed>()->code == sf::Keyboard::Key::Escape)
            {
                window.close();
            }
        }
    }
}

void Application::update()
{
    // We will add logic here later
}

void Application::render()
{
    window.clear(sf::Color::White);

    // We will draw things here later

    window.display();
}
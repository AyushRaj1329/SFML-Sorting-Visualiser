#include "Application.hpp"
#include <iostream>

Application::Application()
    : window(sf::VideoMode({800, 600}), "Sorting Visualizer")
{
    window.setFramerateLimit(60);
    currentState = VisualizerState::WaitingForInput;
    elementCount = 50;
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
            auto keyEvent = event->getIf<sf::Event::KeyPressed>();

            if (keyEvent->code == sf::Keyboard::Key::Escape)
            {
                window.close();
            }

            // 🔹 ENTER LOGIC (Independent of state block)
            if (keyEvent->code == sf::Keyboard::Key::Enter)
            {
                if (currentState == VisualizerState::WaitingForInput)
                {
                    arrayModel.generate(elementCount);
                    currentState = VisualizerState::Ready;
                }
                else if (currentState == VisualizerState::Ready)
                {
                    sortController.start(arrayModel);
                    currentState = VisualizerState::Sorting;
                }
            }

            // 🔹 +/- Only When WaitingForInput
            if (currentState == VisualizerState::WaitingForInput)
            {
                if (keyEvent->code == sf::Keyboard::Key::Add ||
                    keyEvent->code == sf::Keyboard::Key::Equal)
                {
                    if (elementCount < 300)
                        elementCount += 5;
                }

                if (keyEvent->code == sf::Keyboard::Key::Hyphen ||
                    keyEvent->code == sf::Keyboard::Key::Subtract)
                {
                    if (elementCount > 10)
                        elementCount -= 5;
                }
            }
            if (keyEvent->code == sf::Keyboard::Key::Space)
            {
                if (currentState == VisualizerState::Sorting)
                {
                    sortController.pause();
                    currentState = VisualizerState::Paused;
                }
                else if (currentState == VisualizerState::Paused)
                {
                    sortController.resume();
                    currentState = VisualizerState::Sorting;
                }
            }
            if (keyEvent->code == sf::Keyboard::Key::R)
            {
                if (currentState == VisualizerState::Sorting ||
                    currentState == VisualizerState::Paused ||
                    currentState == VisualizerState::Finished)
                {
                    arrayModel.restoreOriginal(); 
                    sortController.restart(arrayModel);
                    currentState = VisualizerState::Sorting;
                }
            }
        }
    }
}

void Application::update()
{
    if (currentState == VisualizerState::Sorting)
    {
        sortController.update(arrayModel);

        if (sortController.isFinished())
        {
            currentState = VisualizerState::Finished;
        }
    }
}

void Application::render()
{
    window.clear(sf::Color::White);

    barRenderer.draw(window, arrayModel);

    window.display();
}
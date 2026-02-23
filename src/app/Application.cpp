#include "Application.hpp"
#include <iostream>
static const unsigned int MIN_WIDTH = 800;
static const unsigned int MIN_HEIGHT = 650;

Application::Application()
    : window(sf::VideoMode({800, 650}),
             "Sorting Visualizer",
             sf::Style::Default)
{
    window.setFramerateLimit(60);
    currentState = VisualizerState::WaitingForInput;
    selectedAlgorithm = AlgorithmType::Bubble;
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

        if (event->is<sf::Event::Resized>())
        {
            auto resized = event->getIf<sf::Event::Resized>();

            unsigned int newWidth = resized->size.x;
            unsigned int newHeight = resized->size.y;

            // 🔹 Enforce minimum size
            if (newWidth < MIN_WIDTH)
                newWidth = MIN_WIDTH;

            if (newHeight < MIN_HEIGHT)
                newHeight = MIN_HEIGHT;

            window.setSize({newWidth, newHeight});

            // 🔹 Update view to match new size
            sf::View view(sf::FloatRect(
                {0.f, 0.f},
                {static_cast<float>(newWidth),
                 static_cast<float>(newHeight)}));

            window.setView(view);
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
                    sortController.start(arrayModel, selectedAlgorithm);
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
            if (keyEvent->code == sf::Keyboard::Key::R &&
                !keyEvent->shift)
            {
                if (currentState == VisualizerState::Sorting ||
                    currentState == VisualizerState::Paused ||
                    currentState == VisualizerState::Finished)
                {
                    arrayModel.restoreOriginal();
                    arrayModel.resetCounters();
                    arrayModel.clearActiveIndices();
                    arrayModel.setSortedRange(-1, -1); // 🔥 CLEAR GREEN

                    sortController.restart(arrayModel);

                    currentState = VisualizerState::Sorting;
                }
            }
            if (keyEvent->code == sf::Keyboard::Key::R &&
                !keyEvent->shift)
            {
                if (currentState == VisualizerState::Sorting ||
                    currentState == VisualizerState::Paused ||
                    currentState == VisualizerState::Finished)
                {
                    arrayModel.restoreOriginal();
                    arrayModel.resetCounters();
                    arrayModel.clearActiveIndices();
                    arrayModel.setSortedRange(-1, -1); // 🔥 CLEAR GREEN

                    sortController.restart(arrayModel);

                    currentState = VisualizerState::Sorting;
                }
            }

            if (keyEvent->code == sf::Keyboard::Key::Period)
            {
                sortController.increaseSpeed();
            }

            if (keyEvent->code == sf::Keyboard::Key::Comma)
            {
                sortController.decreaseSpeed();
            }

            if (currentState == VisualizerState::WaitingForInput ||
                currentState == VisualizerState::Ready)
            {
                if (keyEvent->code == sf::Keyboard::Key::Num1)
                    selectedAlgorithm = AlgorithmType::Bubble;

                if (keyEvent->code == sf::Keyboard::Key::Num2)
                    selectedAlgorithm = AlgorithmType::Selection;

                if (keyEvent->code == sf::Keyboard::Key::Num3)
                    selectedAlgorithm = AlgorithmType::Insertion;

                if (keyEvent->code == sf::Keyboard::Key::Num4)
                    selectedAlgorithm = AlgorithmType::Quick;

                if (keyEvent->code == sf::Keyboard::Key::Num5)
                    selectedAlgorithm = AlgorithmType::Merge;
            }

            if (keyEvent->code == sf::Keyboard::Key::R &&
                keyEvent->shift)
            {
                // FULL RESET

                sortController.reset();
                arrayModel = ArrayModel();
                // arrayModel.resetCounters();
                // arrayModel.clearActiveIndices();

                selectedAlgorithm = AlgorithmType::Bubble;
                elementCount = 50; // or your default

                currentState = VisualizerState::WaitingForInput;
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
    uiOverlay.update(arrayModel, sortController, currentState,
                     selectedAlgorithm,
                     elementCount);
}

void Application::render()
{
    window.clear(sf::Color::White);

    barRenderer.draw(window, arrayModel);
    uiOverlay.draw(window);

    window.display();
}
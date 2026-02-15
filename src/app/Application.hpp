#pragma once

#include <SFML/Graphics.hpp>
#include "../data/ArrayModel.hpp"
#include "../render/BarRenderer.hpp"
#include "../core/VisualizerState.hpp"
#include "../core/SortController.hpp"





using namespace sf;


class Application
{
public:
    Application();
    void run();

private:
    void processEvents();
    void update();
    void render();

    RenderWindow window;
    ArrayModel arrayModel;
    BarRenderer barRenderer;
    VisualizerState currentState;
    int elementCount;
    SortController sortController;



    
};
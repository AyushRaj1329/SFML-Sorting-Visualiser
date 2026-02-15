#include "BarRenderer.hpp"
using namespace sf;

BarRenderer::BarRenderer()
{
    normalColor = sf::Color(100, 149, 237);   // Cornflower Blue
    activeColor = sf::Color::Red;
}

void BarRenderer::draw(sf::RenderWindow& window, const ArrayModel& model)
{
    const std::vector<int>& values = model.getValues();

    if (values.empty())
        return;

    int count = model.size();
    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    float barWidth = windowWidth / count;

    int maxValue = count; // since values go from 1 to n

    for (int i = 0; i < count; ++i)
    {
        float heightRatio = static_cast<float>(values[i]) / maxValue;
        float barHeight = heightRatio * windowHeight;

        RectangleShape bar;
        bar.setSize({ barWidth - 1, barHeight });

        bar.setPosition(Vector2f{
            i * barWidth,
            windowHeight - barHeight}
        );

        if (i == model.getActiveIndex1() || i == model.getActiveIndex2())
            bar.setFillColor(activeColor);
        else
            bar.setFillColor(normalColor);

        window.draw(bar);
    }
}

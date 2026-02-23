#include "BarRenderer.hpp"
using namespace sf;

BarRenderer::BarRenderer()
{
    normalColor = sf::Color(100, 149, 237); // Cornflower Blue
    activeColor = sf::Color::Red;
}
void BarRenderer::draw(sf::RenderWindow &window, const ArrayModel &model)
{
    const std::vector<int> &values = model.getValues();

    if (values.empty())
        return;

    int count = model.size();

    float windowWidth = static_cast<float>(window.getSize().x);
    float windowHeight = static_cast<float>(window.getSize().y);

    // float panelHeight = 150.f; // 🔹 Reserved bottom UI height
    float panelHeight = windowHeight * 0.25f;
    float availableHeight = windowHeight - panelHeight;

    float barWidth = windowWidth / count;
    int maxValue = count; // since values go from 1 to n

    for (int i = 0; i < count; ++i)
    {
        float heightRatio = static_cast<float>(values[i]) / maxValue;
        float barHeight = heightRatio * availableHeight; // 🔹 Use availableHeight

        RectangleShape bar;
        bar.setSize({barWidth - 1, barHeight});

        bar.setPosition(Vector2f{
            i * barWidth,
            availableHeight - barHeight // 🔹 Draw above panel
        });

        int sortedStart = model.getSortedStart();
        int sortedEnd = model.getSortedEnd();

        if (i == model.getActiveIndex1() || i == model.getActiveIndex2())
        {
            bar.setFillColor(activeColor); // 🔴 Active has highest priority
        }
        else if (sortedStart != -1 && i >= sortedStart && i <= sortedEnd)
        {
            bar.setFillColor(sf::Color(40, 200, 120)); // 🟢 Sorted
        }
        else
        {
            bar.setFillColor(normalColor); // 🔵 Default
        }

        window.draw(bar);
    }
}

#include "Map.h"

// Creates the map's initial appearance.
Map::Map()
    : background({ 700.f, 500.f })
{
    background.setFillColor(sf::Color(30, 30, 30));
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(3.f);
}

// Sizes the map with space left around its edges.
void Map::resize(float windowWidth, float windowHeight)
{
    constexpr float horizontalMargin = 50.f;
    constexpr float verticalMargin = 50.f;

    const float boardWidth =
        windowWidth - horizontalMargin * 2.f;

    const float boardHeight =
        windowHeight - verticalMargin * 2.f;

    background.setSize({ boardWidth, boardHeight });

    background.setPosition(
        {
            horizontalMargin,
            verticalMargin
        }
    );
}

// Draws the gameplay area.
void Map::draw(sf::RenderWindow& window) const
{
    window.draw(background);
}

// Provides the map's position and dimensions.
sf::FloatRect Map::getBounds() const
{
    return background.getGlobalBounds();
}

bool Map::contains(const sf::FloatRect& objectBounds) const
{
    const sf::FloatRect mapBounds = background.getGlobalBounds();

    const float objectLeft =
        objectBounds.position.x;

    const float objectTop =
        objectBounds.position.y;

    const float objectRight =
        objectBounds.position.x + objectBounds.size.x;

    const float objectBottom =
        objectBounds.position.y + objectBounds.size.y;

    const float mapLeft =
        mapBounds.position.x;

    const float mapTop =
        mapBounds.position.y;

    const float mapRight =
        mapBounds.position.x + mapBounds.size.x;

    const float mapBottom =
        mapBounds.position.y + mapBounds.size.y;

    return objectLeft >= mapLeft &&
        objectTop >= mapTop &&
        objectRight <= mapRight &&
        objectBottom <= mapBottom;
}
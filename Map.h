#pragma once

#include <SFML/Graphics.hpp>

// Defines and displays the area where gameplay occurs.
class Map
{
public:
    Map();

    // Resizes and centers the board within the window.
    void resize(float windowWidth, float windowHeight);

    // Draws the board background and border.
    void draw(sf::RenderWindow& window) const;

    // Returns the board's boundaries for positioning and collision checks.
    sf::FloatRect getBounds() const;
    // Returns true when the supplied rectangle is fully inside the map.
    bool contains(const sf::FloatRect& objectBounds) const;

private:
    sf::RectangleShape background;
};
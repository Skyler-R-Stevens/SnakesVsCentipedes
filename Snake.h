#pragma once

#include <SFML/Graphics.hpp>

class Snake
{
public:
    Snake();

    void setPosition(sf::Vector2f position);
    void draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape head;
};
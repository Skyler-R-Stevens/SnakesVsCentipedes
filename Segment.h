#pragma once

#include <SFML/Graphics.hpp>

class Segment
{
public:
    explicit Segment(sf::Vector2f size);

    void setPosition(sf::Vector2f position);
    void setColor(sf::Color color);

    void move(sf::Vector2f offset);

    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;

    void draw(sf::RenderWindow& window) const;

private:
    sf::RectangleShape shape;
};
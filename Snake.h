#pragma once

#include <SFML/Graphics.hpp>

#include "Segment.h"

enum class Direction
{
    Up,
    Down,
    Left,
    Right
};

class Snake
{
public:
    Snake();

    // Main actions
    void reset(
        sf::Vector2f startingPosition,
        Direction startingDirection
    );

    void setPosition(sf::Vector2f position);
    void setDirection(Direction newDirection);
    void move(float deltaTime);

    // Drawing
    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;

private:
    Segment head;

    Direction direction;
    float speed;
};
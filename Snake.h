#pragma once

#include <SFML/Graphics.hpp>

#include <cstddef>
#include <vector>

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
    bool hasHitSelf() const;

private:
    void moveOneStep();
    bool isOppositeDirection(Direction newDirection) const;
    sf::Vector2f getMovementOffset(Direction movementDirection) const;

    std::vector<Segment> segments;

    Direction direction;
    Direction nextDirection;

    float moveTimer;
    float moveInterval;

    static constexpr float segmentSize = 30.f;
    static constexpr std::size_t startingLength = 5;
};
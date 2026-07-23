#include "Snake.h"

Snake::Snake()
    : head({ 30.f, 30.f }),
    direction(Direction::Right),
    speed(150.f)
{
    head.setColor(sf::Color::Green);
    head.setPosition({ 100.f, 100.f });
}

void Snake::reset(
    sf::Vector2f startingPosition,
    Direction startingDirection
)
{
    setPosition(startingPosition);
    setDirection(startingDirection);
}

void Snake::setPosition(sf::Vector2f position)
{
    head.setPosition(position);
}

void Snake::setDirection(Direction newDirection)
{
    direction = newDirection;
}

void Snake::move(float deltaTime)
{
    sf::Vector2f movement{ 0.f, 0.f };

    switch (direction)
    {
    case Direction::Up:
        movement.y = -speed * deltaTime;
        break;

    case Direction::Down:
        movement.y = speed * deltaTime;
        break;

    case Direction::Left:
        movement.x = -speed * deltaTime;
        break;

    case Direction::Right:
        movement.x = speed * deltaTime;
        break;
    }

    head.move(movement);
}

void Snake::draw(sf::RenderWindow& window) const
{
    head.draw(window);
}

sf::FloatRect Snake::getBounds() const
{
    return head.getBounds();
}
#include "Snake.h"

Snake::Snake()
    : head({ 30.f, 30.f }),
    direction(Direction::Right),
    speed(150.f)
{
    head.setFillColor(sf::Color::Green);
    head.setPosition({ 100.f, 100.f });
}

void Snake::setPosition(sf::Vector2f position)
{
    head.setPosition(position);
}

void Snake::setDirection(Direction newDirection)
{
    direction = newDirection;
}

// Restores the snake to its starting position and direction.
void Snake::reset(
    sf::Vector2f startingPosition,
    Direction startingDirection
)
{
    setPosition(startingPosition);
    setDirection(startingDirection);
}

void Snake::draw(sf::RenderWindow& window) const
{
    window.draw(head);
}

//Position of the snake's head for collision detection
sf::FloatRect Snake::getBounds() const
{
    return head.getGlobalBounds();
}

//Acceleration function for the snake
void Snake::move(float deltaTime)
{
    sf::Vector2f movement({ 0.f, 0.f });

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
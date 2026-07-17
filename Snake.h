#pragma once

#include <SFML/Graphics.hpp>

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
    //constructor
    Snake();

    //Main Actions
    void reset();
    void setPosition(sf::Vector2f position);
    void setDirection(Direction newDirection);
    void move(float deltaTime);

    //Drawing
    void draw(sf::RenderWindow& window) const;

    sf::FloatRect getBounds() const;

private:
    sf::RectangleShape head;

    Direction direction;
    float speed;
};
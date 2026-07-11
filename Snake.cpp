#include "Snake.h"

Snake::Snake()
    : head({ 30.f, 30.f })
{
    head.setFillColor(sf::Color::Green);
    head.setPosition({ 100.f, 100.f });
}

void Snake::setPosition(sf::Vector2f position)
{
    head.setPosition(position);
}

void Snake::draw(sf::RenderWindow& window) const
{
    window.draw(head);
}
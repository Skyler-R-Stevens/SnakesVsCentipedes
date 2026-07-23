#include "Segment.h"

Segment::Segment(sf::Vector2f size)
    : shape(size)
{
}

void Segment::setPosition(sf::Vector2f position)
{
    shape.setPosition(position);
}

void Segment::setColor(sf::Color color)
{
    shape.setFillColor(color);
}

void Segment::move(sf::Vector2f offset)
{
    shape.move(offset);
}

sf::Vector2f Segment::getPosition() const
{
    return shape.getPosition();
}

sf::FloatRect Segment::getBounds() const
{
    return shape.getGlobalBounds();
}

void Segment::draw(sf::RenderWindow& window) const
{
    window.draw(shape);
}  
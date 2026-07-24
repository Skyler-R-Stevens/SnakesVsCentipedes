#include "Snake.h"

Snake::Snake()
    : direction(Direction::Right),
    nextDirection(Direction::Right),
    moveTimer(0.f),
    moveInterval(0.15f)
{
    reset({ 150.f, 150.f }, Direction::Right);
}

void Snake::reset(
    sf::Vector2f startingPosition,
    Direction startingDirection
)
{
    segments.clear();

    direction = startingDirection;
    nextDirection = startingDirection;
    moveTimer = 0.f;

    const sf::Vector2f movementOffset =
        getMovementOffset(startingDirection);

    for (std::size_t index = 0; index < startingLength; ++index)
    {
        const float distanceBehindHead =
            static_cast<float>(index);

        const sf::Vector2f segmentPosition(
            {
                startingPosition.x
                    - movementOffset.x * distanceBehindHead,

                startingPosition.y
                    - movementOffset.y * distanceBehindHead
            });

        segments.emplace_back(
            sf::Vector2f{ segmentSize, segmentSize }
        );

        segments.back().setPosition(segmentPosition);
        segments.back().setColor(sf::Color::Green);
    }
}

void Snake::setPosition(sf::Vector2f position)
{
    if (segments.empty())
    {
        return;
    }

    const sf::Vector2f currentHeadPosition =
        segments.front().getPosition();

    const sf::Vector2f offset(
        {
            position.x - currentHeadPosition.x,
            position.y - currentHeadPosition.y
        });

    for (Segment& segment : segments)
    {
        segment.move(offset);
    }
}

void Snake::setDirection(Direction newDirection)
{
    if (!isOppositeDirection(newDirection))
    {
        nextDirection = newDirection;
    }
}

void Snake::move(float deltaTime)
{
    moveTimer += deltaTime;

    while (moveTimer >= moveInterval)
    {
        moveOneStep();
        moveTimer -= moveInterval;
    }
}

void Snake::moveOneStep()
{
    if (segments.empty())
    {
        return;
    }

    direction = nextDirection;

    sf::Vector2f previousPosition =
        segments.front().getPosition();

    segments.front().move(
        getMovementOffset(direction)
    );

    for (
        std::size_t index = 1;
        index < segments.size();
        ++index
        )
    {
        const sf::Vector2f currentPosition =
            segments[index].getPosition();

        segments[index].setPosition(previousPosition);

        previousPosition = currentPosition;
    }
}

bool Snake::isOppositeDirection(
    Direction newDirection
) const
{
    switch (direction)
    {
    case Direction::Up:
        return newDirection == Direction::Down;

    case Direction::Down:
        return newDirection == Direction::Up;

    case Direction::Left:
        return newDirection == Direction::Right;

    case Direction::Right:
        return newDirection == Direction::Left;
    }

    return false;
}

sf::Vector2f Snake::getMovementOffset(
    Direction movementDirection
) const
{
    switch (movementDirection)
    {
    case Direction::Up:
        return { 0.f, -segmentSize };

    case Direction::Down:
        return { 0.f, segmentSize };

    case Direction::Left:
        return { -segmentSize, 0.f };

    case Direction::Right:
        return { segmentSize, 0.f };
    }

    return { 0.f, 0.f };
}

void Snake::draw(sf::RenderWindow& window) const
{
    for (const Segment& segment : segments)
    {
        segment.draw(window);
    }
}

sf::FloatRect Snake::getBounds() const
{
    if (segments.empty())
    {
        return {};
    }

    return segments.front().getBounds();
}
bool Snake::hasHitSelf() const
{
    if (segments.size() < 2)
    {
        return false;
    }

    const sf::FloatRect headBounds =
        segments.front().getBounds();

    // Loop goes here.
    for (std::size_t index = 1;
        index < segments.size();
        ++index)
    {
        if (headBounds.findIntersection(
            segments[index].getBounds()))
        {
            return true;
        }
    }

    return false;
}
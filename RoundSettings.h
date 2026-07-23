#pragma once

#include <SFML/System/Vector2.hpp>

#include "Snake.h"

// Contains the starting conditions for one round.
struct RoundSettings
{
    sf::Vector2f snakePosition;
    Direction snakeDirection;
};
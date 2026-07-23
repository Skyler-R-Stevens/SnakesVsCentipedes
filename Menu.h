#pragma once

#include <SFML/Graphics.hpp>
#include "GameMode.h"

class Menu
{
public:
    explicit Menu(const sf::Font& font);

    void resize(float width, float height);
    void draw(sf::RenderWindow& window) const;
    void setSelectedMode(GameMode selectedMode);

private:
    void centerText(sf::Text& text);

    sf::Text title;
    sf::Text startText;
    sf::Text modeText; 
};
#pragma once

#include <SFML/Graphics.hpp>

class Menu
{
public:
    explicit Menu(const sf::Font& font);

    void resize(float width, float height);
    void draw(sf::RenderWindow& window) const;

private:
    void centerText(sf::Text& text);

    sf::Text title;
    sf::Text startText;
};
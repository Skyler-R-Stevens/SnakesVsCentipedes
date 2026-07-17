#pragma once

#include <SFML/Graphics.hpp>

// Owns and displays the text shown when a round ends.
class GameOverScreen
{
public:
    // Creates the game-over text using the shared game font.
    explicit GameOverScreen(const sf::Font& font);

    // Repositions the text to match the current window size.
    void resize(float windowWidth, float windowHeight);

    // Draws the game-over screen.
    void draw(sf::RenderWindow& window) const;

private:
    sf::Text gameOverText;
    sf::Text restartText;
	sf::Text backToMenuText;
};
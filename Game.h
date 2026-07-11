// Snakes Vs Centipedes.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <SFML/Graphics.hpp>

class Game
{
public:
    Game();

    int run();

private:
    void processEvents();
    void handleResize(const sf::Vector2u& newSize);
    void updateTextLayout(float width, float height);
    void render();

    sf::RenderWindow window;

    sf::Font font;
    sf::Text title;
    sf::Text startText;

    sf::RectangleShape snakeHead;

    bool fontLoaded;
    bool gameStarted;
};
// TODO: Reference additional headers your program requires here.

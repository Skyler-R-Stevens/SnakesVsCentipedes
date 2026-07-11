// Snakes Vs Centipedes.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "Snake.h"

class Game
{
    enum class GameState
    {
        MainMenu,
        Playing
    };
public:
    Game();

    int run();

private:
    void processEvents();
    void handleResize(const sf::Vector2u& newSize);
    void render();

    sf::RenderWindow window;

    sf::Font font;
    Menu menu;

    Snake snake;

    bool fontLoaded;
    GameState currentState;
};
// TODO: Reference additional headers your program requires here.

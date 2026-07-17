#pragma once

#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "Snake.h"

// Controls the main application loop and coordinates the game's systems.
class Game
{
private:
    // Represents which major part of the game is currently active.
    enum class GameState
    {
        MainMenu,
        Playing
    };

public:
    // Creates and initializes the game window, menu, and snake.
    Game();

    // Runs the game loop until the window closes.
    // Returns 0 on success or a non-zero value if startup fails.
    int run();

private:
    // Reads window, keyboard, and resize events.
    void processEvents();

    // Updates the SFML view and menu layout after the window is resized.
    void handleResize(const sf::Vector2u& newSize);

	// Ensures the snake remains within the window boundaries.
    void keepSnakeInsideWindow();

    // Draws the current game state to the window.
    void render();

    // The main window where the game is displayed.
    sf::RenderWindow window;

    // Measures time between frames for frame-rate-independent movement.
    sf::Clock clock;

    // Shared font used by text in the game.
    sf::Font font;

    // Objects responsible for the menu and snake behavior.
    Menu menu;
    Snake snake;

    // Records whether the font loaded successfully.
    bool fontLoaded;

    // Stores the currently active game state.
    GameState currentState;
};
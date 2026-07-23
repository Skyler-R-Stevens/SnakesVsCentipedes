#pragma once

#include <SFML/Graphics.hpp>

#include "Menu.h"
#include "Snake.h"
#include "GameOverScreen.h"
#include "Map.h"
#include "GameMode.h"
#include "RoundSettings.h"

// Controls the main application loop and coordinates the game's systems.
class Game
{
private:
    // Represents which major part of the game is currently active.
    enum class GameState
    {
        MainMenu,
        Playing,
        GameOver
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

	// See if the snake has collided with the window boundaries.
    bool hasSnakeHitWall() const;

    // Draws the current game state to the window.
    void render();

	// Guarantees that the game is ready for a new round of play.
    void selectGameMode(GameMode newMode);
    RoundSettings createRoundSettings() const;
    void startNewRound();

    // The main window where the game is displayed.
    sf::RenderWindow window;

    // Measures time between frames for frame-rate-independent movement.
    sf::Clock clock;

    // Shared font used by text in the game.
    sf::Font font;

    // Objects responsible for the menu, snake, and game over screen behavior.
    Menu menu;
    GameOverScreen gameOverScreen;
    Map map;
    Snake snake;

    // Records whether the font loaded successfully.
    bool fontLoaded;

    // Stores the currently active game state/Mode.
    GameMode selectedMode;
    GameState currentState;

};
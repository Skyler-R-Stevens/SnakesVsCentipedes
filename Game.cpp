#include "Game.h"
//#include <algorithm>

//This is the constructor for the game class, it initializes the window and all major game components.
Game::Game()
    : window(
        sf::VideoMode({ 800, 600 }),
        "Snakes Vs. Centipedes"
    ),
    menu(font),
	gameOverScreen(font),
    map(),
    snake(),
    fontLoaded(false),
    selectedMode(GameMode::Classic),
    currentState(GameState::MainMenu) 
{
    fontLoaded = font.openFromFile(
        "assets/fonts/Roboto-VariableFont_wdth,wght.ttf"
    );


    const sf::Vector2u windowSize = window.getSize();

    const float windowWidth =
        static_cast<float>(windowSize.x);

    const float windowHeight =
        static_cast<float>(windowSize.y);

    menu.resize(windowWidth, windowHeight);
    gameOverScreen.resize(windowWidth, windowHeight);
    map.resize(windowWidth, windowHeight);

    menu.setSelectedMode(selectedMode);
}

//This is the main game loop, it runs until the window closes.
int Game::run()
{
    if (!fontLoaded)
    {
        return -1;
    }

    while (window.isOpen())
    {
        const float deltaTime = clock.restart().asSeconds();

        processEvents();

        if (currentState == GameState::Playing)
        {
            snake.move(deltaTime);

            if (hasSnakeHitWall())
            {
                currentState = GameState::GameOver;
            }
            if (hasSnakeHitWall() || snake.hasHitSelf())
            {
                currentState = GameState::GameOver;
            }
        }

        render();
    }

    return 0;
}

// Processes window, keyboard, and resize events.
void Game::processEvents()
{
    while (const auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        // Handles keyboard input for the menu and gameplay.
        if (const auto* keyPressed =
            event->getIf<sf::Event::KeyPressed>())
        {
            if (currentState == GameState::MainMenu)
            {
                switch (keyPressed->code)
                {
                case sf::Keyboard::Key::Num1:
                    selectGameMode(GameMode::Classic);
                    break;

                case sf::Keyboard::Key::Num2:
                    selectGameMode(GameMode::ArenaTest);
                    break;

                case sf::Keyboard::Key::Enter:
                    startNewRound();
                    break;

                default:
                    break;
                }
            }
            else if (currentState == GameState::GameOver)
            {
                if (keyPressed->code == sf::Keyboard::Key::Enter)
                {
                    startNewRound();
                }
                else if (keyPressed->code == sf::Keyboard::Key::Escape)
                {
                    currentState = GameState::MainMenu;
                }
            }
            else
            {
                switch (keyPressed->code)
                {
                case sf::Keyboard::Key::Up:
                    snake.setDirection(Direction::Up);
                    break;

                case sf::Keyboard::Key::Down:
                    snake.setDirection(Direction::Down);
                    break;

                case sf::Keyboard::Key::Left:
                    snake.setDirection(Direction::Left);
                    break;

                case sf::Keyboard::Key::Right:
                    snake.setDirection(Direction::Right);
                    break;

				case sf::Keyboard::Key::Escape:
					currentState = GameState::MainMenu;
                    break;

                default:
                    break;
                }
            }
        }
        // Responds when the window size changes.
        if (const auto* resized =
            event->getIf<sf::Event::Resized>())
        {
            handleResize(resized->size);
        }
    }
}

// Updates the view and menu layout to match the new window size.
void Game::handleResize(const sf::Vector2u& newSize)
{
    const float width = static_cast<float>(newSize.x);
    const float height = static_cast<float>(newSize.y);

    sf::View resizedView(
        sf::FloatRect(
            { 0.f, 0.f },
            { width, height }
        )
    );

    window.setView(resizedView);

    menu.resize(width, height);
    gameOverScreen.resize(width, height);
    map.resize(width, height);
}

// Reports whether the snake has moved outside the map.
bool Game::hasSnakeHitWall() const
{
    return !map.contains(snake.getBounds());
}

// Prepares all gameplay data and begins a fresh round.
void Game::startNewRound()
{
    const RoundSettings settings = createRoundSettings();

    snake.reset(
        settings.snakePosition,
        settings.snakeDirection
    );

    currentState = GameState::Playing;
}

// Sets the game mode for the next round.
void Game::selectGameMode(GameMode newMode)
{
    selectedMode = newMode;
    menu.setSelectedMode(selectedMode);
}

// Creates the starting conditions for the currently selected game mode.
RoundSettings Game::createRoundSettings() const
{
    const sf::FloatRect mapBounds = map.getBounds();

    switch (selectedMode)
    {
    case GameMode::Classic:
        return RoundSettings{
            {
                mapBounds.position.x + 150.f,
                mapBounds.position.y + 150.f
            },
            Direction::Right
        };

    case GameMode::ArenaTest:
        return RoundSettings{
            {
                mapBounds.position.x +
                    mapBounds.size.x / 2.f,

                mapBounds.position.y +
                    mapBounds.size.y / 2.f
            },
            Direction::Up
        };
    }

    // Defensive fallback in case another mode is added incorrectly.
    return RoundSettings{
        {
            mapBounds.position.x + 150.f,
            mapBounds.position.y + 150.f
        },
        Direction::Right
    };
}

// Draws the menu or gameplay depending on the current game state.
void Game::render()
{
    window.clear();

    switch (currentState)
    {
    case GameState::MainMenu:
        menu.draw(window);
        break;

    case GameState::Playing:
        map.draw(window);
        snake.draw(window);
        break;
    case GameState::GameOver:
        gameOverScreen.draw(window);
        break;
    }
    window.display();
}

#include "Game.h"
#include <algorithm>

//This is the constructor for the game class, it initializes the window, menu, snake, and font
Game::Game()
    : window(
        sf::VideoMode({ 800, 600 }),
        "Snakes Vs. Centipedes"
    ),
    menu(font),
	gameOverScreen(font),
    snake(),
    fontLoaded(false),
    currentState(GameState::MainMenu) 
{
    fontLoaded = font.openFromFile(
        "assets/fonts/Roboto-VariableFont_wdth,wght.ttf"
    );


    const sf::Vector2u windowSize = window.getSize();

    menu.resize(
        static_cast<float>(windowSize.x),
        static_cast<float>(windowSize.y)
    );
    gameOverScreen.resize(
        static_cast<float>(windowSize.x),
        static_cast<float>(windowSize.y)
    );
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
                if (keyPressed->code == sf::Keyboard::Key::Enter)
                {
                    currentState = GameState::Playing;
                }
            }
            else if(currentState == GameState::GameOver)
            {
                if (keyPressed->code == sf::Keyboard::Key::Enter)
                {
                    // Reset the game state
                    currentState = GameState::Playing;
                    snake.reset();
                }
                if (keyPressed->code == sf::Keyboard::Key::Escape)
                {
                    // Reset the game state
                    currentState = GameState::MainMenu;
                    snake.reset();
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
}

// Clamps the snake's position so it remains inside the window.
bool Game::hasSnakeHitWall() const
{
    const sf::FloatRect snakeBounds = snake.getBounds();
    const sf::Vector2u windowSize = window.getSize();

    const float windowWidth =
        static_cast<float>(windowSize.x);

    const float windowHeight =
        static_cast<float>(windowSize.y);

    const bool hitLeftWall =
        snakeBounds.position.x < 0.f;

    const bool hitTopWall =
        snakeBounds.position.y < 0.f;

    const bool hitRightWall =
        snakeBounds.position.x + snakeBounds.size.x > windowWidth;

    const bool hitBottomWall =
        snakeBounds.position.y + snakeBounds.size.y > windowHeight;

    return hitLeftWall ||
        hitTopWall ||
        hitRightWall ||
        hitBottomWall;
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
        snake.draw(window);
        break;
    case GameState::GameOver:
        gameOverScreen.draw(window);
        break;
    }
    window.display();
}

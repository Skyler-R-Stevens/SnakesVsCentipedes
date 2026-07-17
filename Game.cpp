#include "Game.h"
#include <algorithm>

//This is the constructor for the game class, it initializes the window, menu, snake, and font
Game::Game()
    : window(
        sf::VideoMode({ 800, 600 }),
        "Snakes Vs. Centipedes"
    ),
    menu(font),
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
            keepSnakeInsideWindow();
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
}

// Clamps the snake's position so it remains inside the window.
void Game::keepSnakeInsideWindow()
{
    const sf::FloatRect snakeBounds = snake.getBounds();
    const sf::Vector2u windowSize = window.getSize();

    sf::Vector2f correctedPosition = snakeBounds.position;

    const float maximumX =
        static_cast<float>(windowSize.x) - snakeBounds.size.x;

    const float maximumY =
        static_cast<float>(windowSize.y) - snakeBounds.size.y;

    correctedPosition.x =
        std::clamp(correctedPosition.x, 0.f, maximumX);

    correctedPosition.y =
        std::clamp(correctedPosition.y, 0.f, maximumY);

    snake.setPosition(correctedPosition);
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
    }
    window.display();
}

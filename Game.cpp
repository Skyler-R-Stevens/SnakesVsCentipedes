#include "Game.h"
#include <algorithm>

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

int Game::run()
{
    if (!fontLoaded)
    {
        return -1;
    }

    while (window.isOpen())
    {
        processEvents();
        render();
    }

    return 0;
}

void Game::processEvents()
{
    while (const auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
        {
            window.close();
        }

        if (const auto* keyPressed =
            event->getIf<sf::Event::KeyPressed>())
        {
            if (keyPressed->code == sf::Keyboard::Key::Enter)
            {
                currentState = GameState::Playing;
            }
        }

        if (const auto* resized =
            event->getIf<sf::Event::Resized>())
        {
            handleResize(resized->size);
        }
    }
}

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
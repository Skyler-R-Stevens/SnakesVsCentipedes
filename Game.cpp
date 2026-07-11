#include "Game.h"

#include <algorithm>

Game::Game()
    : window(
        sf::VideoMode({ 800, 600 }),
        "Snakes Vs. Centipedes"
    ),
    title(font),
    startText(font),
    snakeHead({ 30.f, 30.f }),
    fontLoaded(false),
    gameStarted(false)
{
    fontLoaded = font.openFromFile(
        "assets/fonts/Roboto-VariableFont_wdth,wght.ttf"
    );

    title.setString("Snakes Vs. Centipedes");
    title.setCharacterSize(48);

    startText.setString("Press Enter to Start");
    startText.setCharacterSize(28);

    snakeHead.setFillColor(sf::Color::Green);
    snakeHead.setPosition({ 100.f, 100.f });

    const sf::Vector2u windowSize = window.getSize();

    updateTextLayout(
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
                gameStarted = true;
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

    updateTextLayout(width, height);
}

void Game::updateTextLayout(float width, float height)
{
    const unsigned int titleSize =
        static_cast<unsigned int>(
            std::clamp(width * 0.06f, 24.f, 72.f)
            );

    const unsigned int startSize =
        static_cast<unsigned int>(
            std::clamp(width * 0.035f, 16.f, 40.f)
            );

    title.setCharacterSize(titleSize);
    startText.setCharacterSize(startSize);

    const sf::FloatRect titleBounds = title.getLocalBounds();

    title.setOrigin({
        titleBounds.position.x + titleBounds.size.x / 2.f,
        titleBounds.position.y + titleBounds.size.y / 2.f
        });

    const sf::FloatRect startBounds = startText.getLocalBounds();

    startText.setOrigin({
        startBounds.position.x + startBounds.size.x / 2.f,
        startBounds.position.y + startBounds.size.y / 2.f
        });

    title.setPosition({
        width / 2.f,
        height * 0.42f
        });

    startText.setPosition({
        width / 2.f,
        height * 0.58f
        });
}

void Game::render()
{
    window.clear();

    if (!gameStarted)
    {
        window.draw(title);
        window.draw(startText);
    }
    else
    {
        window.draw(snakeHead);
    }

    window.display();
}
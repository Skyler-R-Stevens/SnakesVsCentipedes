#include "GameOverScreen.h"

// Creates the game-over screen's text objects.
GameOverScreen::GameOverScreen(const sf::Font& font)
    : gameOverText(font),
    restartText(font),
	backToMenuText(font)
{
    gameOverText.setString("Game Over");
    gameOverText.setCharacterSize(64);

    restartText.setString("Press Enter to Restart");
    restartText.setCharacterSize(30);

    backToMenuText.setString("Press Escape to Return to Menu");
    backToMenuText.setCharacterSize(30);
}

// Centers the game-over text in the window.
void GameOverScreen::resize(
    float windowWidth,
    float windowHeight
)
{
    const sf::FloatRect gameOverBounds =
        gameOverText.getLocalBounds();

    gameOverText.setOrigin(
        {
            gameOverBounds.position.x +
                gameOverBounds.size.x / 2.f,

            gameOverBounds.position.y +
                gameOverBounds.size.y / 2.f
        }
    );

    gameOverText.setPosition(
        {
            windowWidth / 2.f,
            windowHeight * 0.4f
        }
    );

    const sf::FloatRect restartBounds =
        restartText.getLocalBounds();

    restartText.setOrigin(
        {
            restartBounds.position.x +
                restartBounds.size.x / 2.f,

            restartBounds.position.y +
                restartBounds.size.y / 2.f
        }
    );

    restartText.setPosition(
        {
            windowWidth / 2.f,
            windowHeight * 0.6f
        }
    );

    const sf::FloatRect backToMenuBounds =
        backToMenuText.getLocalBounds();

    backToMenuText.setOrigin(
        {
            backToMenuBounds.position.x +
                backToMenuBounds.size.x / 2.f,

            backToMenuBounds.position.y +
                backToMenuBounds.size.y / 2.f
        }
    );

    backToMenuText.setPosition(
        {
            windowWidth / 2.f,
            windowHeight * 0.8f
        }
    );
}

// Draws all game-over text.
void GameOverScreen::draw(sf::RenderWindow& window) const
{
    window.draw(gameOverText);
    window.draw(restartText);
    window.draw(backToMenuText);
}   
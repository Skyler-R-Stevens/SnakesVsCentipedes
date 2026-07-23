#include "Menu.h"
#include <algorithm>

Menu::Menu(const sf::Font& font)
    : title(font),
    startText(font),
    modeText(font)
{
    title.setString("Snakes Vs. Centipedes");
    title.setCharacterSize(48);

    startText.setString(
        "Press 1 for Classic\n"
        "Press 2 for Arena Test\n"
        "Press Enter to Start"
    );
    startText.setCharacterSize(28);

    modeText.setString("Selected Mode: Classic");
    modeText.setCharacterSize(24);
}

void Menu::resize(float width, float height)
{
    const unsigned int titleSize =
        static_cast<unsigned int>(
            std::clamp(width * 0.06f, 24.f, 72.f)
            );

    const unsigned int startSize =
        static_cast<unsigned int>(
            std::clamp(width * 0.035f, 16.f, 40.f)
            );

    const unsigned int modeSize =
        static_cast<unsigned int>(
            std::clamp(width * 0.03f, 16.f, 34.f)
            );

    title.setCharacterSize(titleSize);
    startText.setCharacterSize(startSize);
    modeText.setCharacterSize(modeSize);

    centerText(title);
    centerText(modeText);
    centerText(startText);

    title.setPosition(
        {
            width / 2.f,
            height * 0.30f
        }
    );

    modeText.setPosition(
        {
            width / 2.f,
            height * 0.48f
        }
    );

    startText.setPosition(
        {
            width / 2.f,
            height * 0.68f
        }
    );
}

void Menu::setSelectedMode(GameMode selectedMode)
{
    switch (selectedMode)
    {
    case GameMode::Classic:
        modeText.setString("Selected Mode: Classic");
        break;

    case GameMode::ArenaTest:
        modeText.setString("Selected Mode: Arena Test");
        break;
    }

    // The text width may change, so recenter its origin.
    centerText(modeText);
}

void Menu::draw(sf::RenderWindow& window) const
{
    window.draw(title);
    window.draw(modeText);
    window.draw(startText);
}

void Menu::centerText(sf::Text& text)
{
    const sf::FloatRect bounds = text.getLocalBounds();

    text.setOrigin(
        {
            bounds.position.x + bounds.size.x / 2.f,
            bounds.position.y + bounds.size.y / 2.f
        }
    );
}
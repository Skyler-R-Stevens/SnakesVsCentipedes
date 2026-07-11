#include "Menu.h"

#include <algorithm>

Menu::Menu(const sf::Font& font)
    : title(font),
    startText(font)
{
    title.setString("Snakes Vs. Centipedes");
    title.setCharacterSize(48);

    startText.setString("Press Enter to Start");
    startText.setCharacterSize(28);
}

void Menu::resize(float width, float height)
{
    const unsigned int titleSize = static_cast<unsigned int>(
        std::clamp(width * 0.06f, 24.f, 72.f)
        );

    const unsigned int startSize = static_cast<unsigned int>(
        std::clamp(width * 0.035f, 16.f, 40.f)
        );

    title.setCharacterSize(titleSize);
    startText.setCharacterSize(startSize);

    centerText(title);
    centerText(startText);

    title.setPosition({
        width / 2.f,
        height * 0.42f
        });

    startText.setPosition({
        width / 2.f,
        height * 0.58f
        });
}

void Menu::draw(sf::RenderWindow& window) const
{
    window.draw(title);
    window.draw(startText);
}

void Menu::centerText(sf::Text& text)
{
    const sf::FloatRect bounds = text.getLocalBounds();

    text.setOrigin({
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y / 2.f
        });
}
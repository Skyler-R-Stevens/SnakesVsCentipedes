#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(
        sf::VideoMode({ 800, 600 }),
        "Snakes Vs. Centipedes"
    );

    sf::Font font;

    if (!font.openFromFile("assets/fonts/Roboto-VariableFont_wdth,wght.ttf"))
    {
        return -1;
    }

    sf::Text title(font);

    title.setString("Snakes Vs. Centipedes");
    title.setCharacterSize(48);
    title.setPosition({ 140.f, 250.f });

    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }

        window.clear();
        window.draw(title);
        window.display();
    }

    return 0;
}
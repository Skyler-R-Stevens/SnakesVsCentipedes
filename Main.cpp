#include <SFML/Graphics.hpp>
#include <algorithm>

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

    const sf::FloatRect titleBounds = title.getLocalBounds();

    title.setOrigin({
        titleBounds.position.x + titleBounds.size.x / 2.f,
        titleBounds.position.y + titleBounds.size.y / 2.f
        });

    const sf::Vector2u windowSize = window.getSize();

    title.setPosition({
        static_cast<float>(windowSize.x) / 2.f,
        static_cast<float>(windowSize.y) * 0.42f
        });

    sf::Text startText(font);

    startText.setString("Press Enter to Start");
    startText.setCharacterSize(28);

    const sf::FloatRect startBounds = startText.getLocalBounds();

    startText.setOrigin({
        startBounds.position.x + startBounds.size.x / 2.f,
        startBounds.position.y + startBounds.size.y / 2.f
        });

    startText.setPosition({
    static_cast<float>(windowSize.x) / 2.f,
    static_cast<float>(windowSize.y) * 0.58f
        });


    while (window.isOpen())
    {
        while (const auto event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
            //if (event->is<sf::Event::Resized>())
            {
                if (const auto* resized = event->getIf<sf::Event::Resized>())
                {
                    const float newWidth = static_cast<float>(resized->size.x);
                    const float newHeight = static_cast<float>(resized->size.y);

                    const unsigned int titleSize = static_cast<unsigned int>(
                        std::clamp(newWidth * 0.06f, 24.f, 72.f)
                        );

                    const unsigned int startSize = static_cast<unsigned int>(
                        std::clamp(newWidth * 0.035f, 16.f, 40.f)
                        );

                    title.setCharacterSize(titleSize);
                    startText.setCharacterSize(startSize);

                    const sf::FloatRect newTitleBounds = title.getLocalBounds();

                    title.setOrigin({
                        newTitleBounds.position.x + newTitleBounds.size.x / 2.f,
                        newTitleBounds.position.y + newTitleBounds.size.y / 2.f
                        });

                    const sf::FloatRect newStartBounds = startText.getLocalBounds();

                    startText.setOrigin({
                        newStartBounds.position.x + newStartBounds.size.x / 2.f,
                        newStartBounds.position.y + newStartBounds.size.y / 2.f
                        });

                    sf::View resizedView(sf::FloatRect(
                        { 0.f, 0.f },
                        { newWidth, newHeight }
                    ));

                    window.setView(resizedView);

                    title.setPosition({
                        newWidth / 2.f,
                        newHeight * 0.42f
                        });

                    startText.setPosition({
                        newWidth / 2.f,
                        newHeight * 0.58f
                        });
                }
            }
        }

        window.clear();

        window.draw(title);
        window.draw(startText);

        window.display();
    }

    return 0;
}
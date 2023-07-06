#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");

    sf::Font font;
    if (!font.loadFromFile("../resources/font/arial.ttf"))
    {
        std::cout << "Font Loading Error!" << std::endl;
    }

    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Text text;
    text.setFont(font);
    text.setString("Hello SFML!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();

        window.draw(shape);
        window.draw(text);

        window.display();
    }

    return 0;
}
#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player(const sf::Vector2f pos, float size, sf::Color color, float speed);

    void Update();

    void Draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() { return position; }
private:
    void ProcessInput();

private:
    sf::Vector2f position;
    float speed;

    sf::RectangleShape shape;
    float size;
    sf::Color color;
};
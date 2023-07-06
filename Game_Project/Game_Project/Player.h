#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player(const sf::Vector2f pos, float size, sf::Color color, float speed)
        : position{ pos }, size{ size }, color{ color }, speed{ speed }
    {
        shape = sf::RectangleShape{ sf::Vector2f{size, size} };
        shape.setFillColor(color);
    }

    void Update()
    {
        ProcessInput();
        shape.setPosition(position);
    }

    void Draw(sf::RenderWindow& window)
    {
        window.draw(shape);
    }

    sf::Vector2f getPosition() { return position; }
private:
    void ProcessInput()
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            position.x -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            position.x += speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            position.y -= speed;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            position.y += speed;
        }
    }

private:
    sf::Vector2f position;
    float speed;

    sf::RectangleShape shape;
    float size;
    sf::Color color;
};
#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
    Bullet(const sf::Vector2f& pos, const sf::Vector2f& direction,
        float size, const sf::Color& color, float speed)
        : position{ pos }, direction{ direction },
        size{ size }, color{ color }, speed{ speed }
    {
        shape = sf::CircleShape{ size };
        shape.setFillColor(color);
        shape.setOutlineColor(sf::Color::Green);
        shape.setOutlineThickness(0.3f);
    }

    Bullet()
        : Bullet{ sf::Vector2f{0,0}, sf::Vector2f{1.0f,0}, 0.3f, sf::Color{255,255,0,255}, 5.0f }
    {}

    void Update()
    {
        UpdatePosition();
        shape.setPosition(position);
    }

    void Draw(sf::RenderWindow& window)
    {
        window.draw(shape);
    }

    sf::Vector2f getPosition() const { return position; }

private:
    void UpdatePosition()
    {
        position += direction * speed;
        shape.setPosition(position);
    }

private:
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;

    sf::CircleShape shape;
    float size;
    sf::Color color;
};
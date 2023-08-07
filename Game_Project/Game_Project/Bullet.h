#pragma once

#include <SFML/Graphics.hpp>

class Bullet
{
public:
    Bullet(const sf::Vector2f& pos, const sf::Vector2f& direction,
        float size, const sf::Color& color, float speed);

    Bullet();

    void Update();

    void Draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const { return position; }

private:
    void UpdatePosition();

private:
    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;

    sf::CircleShape shape;
    float size;
    sf::Color color;
};
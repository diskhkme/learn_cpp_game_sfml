#pragma once

#include <SFML/Graphics.hpp>
#include "Game.h"

class Bullet
{
public:
    Bullet(Game *game, sf::Vector2f initPos, sf::Vector2f initDir)
        : position{ initPos }, direction{ initDir }
    {
        shape = sf::CircleShape{ size };
        shape.setFillColor(color);
        shape.setOutlineColor(sf::Color::Green);
        shape.setOutlineThickness(0.3f);

        size = 3.0f;
        color = sf::Color{ 0,255,0,255 };
        speed = 500.0f;
    }

    Bullet()
        : Bullet{ nullptr, sf::Vector2f{0,0}, sf::Vector2f{1.0f,0} }
    {}

    void Update(float dt)
    {
        UpdatePosition(dt);
        shape.setPosition(position);
    }

    void Draw(sf::RenderWindow& window)
    {
        window.draw(shape);
    }

    sf::Vector2f getPosition() const { return position; }

private:
    void UpdatePosition(float dt)
    {
        position += direction * speed * dt;
    }

private:
    Game* game;

    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;

    sf::CircleShape shape;
    float size;
    sf::Color color;
};
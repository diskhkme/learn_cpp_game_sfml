#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Enemy
{
public:
    Enemy(const sf::Vector2f pos, float size, sf::Color color, float speed,
        const Player* player) // dependency injection
        : position{ pos }, size{ size }, color{ color }, speed{ speed }, playerRef{player}
    {
        shape = sf::CircleShape{ size };
        shape.setFillColor(color);
        shape.setOutlineColor(sf::Color::Red);
        shape.setOutlineThickness(1.0f);
    }

    Enemy()
        : Enemy{ sf::Vector2f{0,0}, 1.0f, sf::Color{255,255,0,255}, 1.0f, nullptr }
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
        sf::Vector2f playerPosition = playerRef->getPosition();

        float enemyToPlayerX = playerPosition.x - position.x;
        float enemyToPlayerY = playerPosition.y - position.y;

        float length = sqrt(enemyToPlayerX * enemyToPlayerX + enemyToPlayerY * enemyToPlayerY);

        enemyToPlayerX /= length;
        enemyToPlayerY /= length;

        position.x += enemyToPlayerX * speed;
        position.y += enemyToPlayerY * speed;
    }

private:
    sf::Vector2f position;
    float speed;
    const Player* playerRef;

    sf::CircleShape shape;
    float size;
    sf::Color color;
};
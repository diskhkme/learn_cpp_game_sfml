#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"

class Enemy
{
public:
    Enemy(Game* game, sf::Vector2f initPos)
        : game{game}, position{initPos}
    {
        size = 3.0f;
        speed = 200.0f;

        sf::Sprite shape;
        shape.setTexture(game->GetShipTexture());
        shape.setTextureRect(sf::IntRect{ 40,0,8,8 });

        shape.setScale(sf::Vector2f{ size,size });
        sf::FloatRect bounds = shape.getLocalBounds();
        shape.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
    }

    Enemy()
        : Enemy{ nullptr, sf::Vector2f{0,0} }
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
        sf::Vector2f playerPosition = game->GetPlayer()->getPosition();

        sf::Vector2f enemyToPlayer = playerPosition - position;

        float length = sqrt(enemyToPlayer.x * enemyToPlayer.x + enemyToPlayer.y * enemyToPlayer.y);

        enemyToPlayer /= length;

        position += enemyToPlayer * speed * dt;
    }

private:
    Game* game;

    sf::Vector2f position;
    float speed;

    sf::Sprite shape;
    float size;
};
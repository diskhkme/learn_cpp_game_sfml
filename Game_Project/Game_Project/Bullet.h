#pragma once

#include <SFML/Graphics.hpp>

class Game;

class Bullet
{
public:
    Bullet(Game* game, float size, float speed);

    Bullet();

    void Update(float dt);

    void Draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const { return position; }

private:
    void UpdatePosition(float dt);
    sf::Vector2f GetPlayerToClosestEnemyVector();

private:
    Game* game;

    sf::Vector2f position;
    sf::Vector2f direction;
    float speed;

    sf::Sprite shape;
    float size;
};
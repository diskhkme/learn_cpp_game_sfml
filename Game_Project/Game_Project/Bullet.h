#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.h"

class Game;

class Bullet : public Actor
{
public:
    Bullet(Game* game, float size, float speed);

    Bullet();

    void Update(float dt);

private:
    void UpdatePosition(float dt);
    sf::Vector2f GetPlayerToClosestEnemyVector();

private:
    sf::Vector2f direction;
    
};
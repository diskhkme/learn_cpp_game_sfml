#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.h"

class Game;

class Bullet : public Actor
{
public:
    Bullet(Game* game, ActorType type, float size, float speed);

    Bullet();

    virtual ~Bullet();

    virtual void Update(float dt) override;

private:
    void UpdatePosition(float dt);
    sf::Vector2f GetPlayerToClosestEnemyVector();

private:
    sf::Vector2f direction;
    
};
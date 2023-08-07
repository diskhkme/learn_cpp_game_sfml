#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.h"

class Player;
class Game;

class Enemy : public Actor
{
public:
    Enemy(Game* game, const sf::Vector2f pos, float size, float speed);
    Enemy();
    virtual ~Enemy();

    virtual void Update(float dt) override;

private:
    void UpdatePosition(float dt);

private:
    
};
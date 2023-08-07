#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.h"

class Game;

class Player: public Actor
{
public:
    Player(Game* game, ActorType type, const sf::Vector2f pos, float size, float speed);
    virtual ~Player();

    virtual void Update(float dt) override;

private:
    void ProcessInput(float dt);

private:

};
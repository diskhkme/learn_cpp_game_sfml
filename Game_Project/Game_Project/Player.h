#pragma once

#include <SFML/Graphics.hpp>
#include "Actor.h"

class Game;

class Player: public Actor
{
public:
    Player(Game* game, const sf::Vector2f pos, float size, float speed);

    void Update(float dt);

private:
    void ProcessInput(float dt);

private:

};
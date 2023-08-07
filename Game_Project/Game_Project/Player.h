#pragma once

#include <SFML/Graphics.hpp>

class Game;

class Player
{
public:
    Player(Game* game, const sf::Vector2f pos, float size, float speed);

    void Update(float dt);

    void Draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const { return position; }
private:
    void ProcessInput(float dt);

private:
    Game* game;

    sf::Vector2f position;
    float speed;

    sf::Sprite shape;
    float size;
};
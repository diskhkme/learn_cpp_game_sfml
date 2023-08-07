#pragma once

#include <SFML/Graphics.hpp>

class Player;
class Game;

class Enemy
{
public:
    Enemy(Game* game, const sf::Vector2f pos, float size, sf::Color color, float speed);
    Enemy();

    void Update(float dt);

    void Draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const { return position; }

private:
    void UpdatePosition(float dt);

private:
    Game* game;

    sf::Vector2f position;
    float speed;

    sf::CircleShape shape;
    float size;
    sf::Color color;
};
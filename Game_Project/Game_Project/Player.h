#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
    Player(const sf::Vector2f pos, float size, sf::Color color, float speed);

    void Update(float dt);

    void Draw(sf::RenderWindow& window);

    sf::Vector2f getPosition() const { return position; }
private:
    void ProcessInput(float dt);

private:
    sf::Vector2f position;
    float speed;

    sf::RectangleShape shape;
    float size;
    sf::Color color;
};
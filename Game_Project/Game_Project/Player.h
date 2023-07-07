#pragma once

#include <SFML/Graphics.hpp>

class Game;

class Player
{
public:
    Player(Game* game, sf::Vector2f initPos)
        : game{game}, position{initPos}
    {
        size = 3.0f;
        speed = 100.0f;

        sf::Sprite shape;
        shape.setTexture(game->GetShipTexture());
        shape.setTextureRect(sf::IntRect{ 8,0,8,8 });

        shape.setScale(sf::Vector2f{ size,size });
        sf::FloatRect bounds = shape.getLocalBounds();
        shape.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
      
    }

    void Update(float dt)
    {
        ProcessInput(dt);
        shape.setPosition(position);
    }

    void Draw(sf::RenderWindow& window)
    {
        window.draw(shape);
    }

    sf::Vector2f getPosition() const { return position; }
private:
    void ProcessInput(float dt)
    {
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
        {
            position.x -= speed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
        {
            position.x += speed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
        {
            position.y -= speed * dt;
        }
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
        {
            position.y += speed * dt;
        }
    }

private:
    Game* game;

    sf::Vector2f position;
    float speed;

    sf::Sprite shape;
    float size;
};
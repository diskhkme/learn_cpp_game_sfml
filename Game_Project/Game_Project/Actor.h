#pragma once

#include <SFML/Graphics.hpp>

class Game;

class Actor
{
public:
	Actor(Game* game, sf::Vector2f pos, float speed, float size);

	void Update(float dt);

	void Draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() const { return position; }

protected:
	Game* game;
	
	sf::Vector2f position;
	float speed;

	sf::Sprite shape;
	float size;
};

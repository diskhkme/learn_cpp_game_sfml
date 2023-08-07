#pragma once

#include <SFML/Graphics.hpp>

class Game;

enum ActorType
{
	PLAYER, ENEMY, BULLET,
};

class Actor
{
public:
	Actor(Game* game, ActorType type, sf::Vector2f pos, float speed, float size);
	virtual ~Actor();

	virtual void Update(float dt) = 0;

	void Draw(sf::RenderWindow& window);

	sf::Vector2f getPosition() const { return position; }

	ActorType GetActorType() const { return type; }

	bool GetIsActive() const { return isActive; }
	void SetIsActive(bool b) { isActive = b; }

protected:
	Game* game;

	ActorType type;
	bool isActive;
	
	sf::Vector2f position;
	float speed;

	sf::Sprite shape;
	float size;
};

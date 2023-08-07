#include "Actor.h"

Actor::Actor(Game* game, ActorType type, sf::Vector2f pos, float speed, float size)
	:game{ game }, type{ type }, position {	pos}, speed{ speed }, size{ size }, isActive{true}
{
}

Actor::~Actor()
{
}

void Actor::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

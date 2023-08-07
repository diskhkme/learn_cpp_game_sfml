#include "Player.h"
#include "Game.h"


Player::Player(Game* game, ActorType type, const sf::Vector2f pos, float size, float speed)
	: Actor{ game, type, pos, speed, size }
{
	shape.setTexture(this->game->GetShipTexture());
	shape.setTextureRect(sf::IntRect{ 8,0,8,8 });

	shape.setScale(sf::Vector2f{ size,size });
	sf::FloatRect bounds = shape.getLocalBounds();
	shape.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

Player::~Player()
{
}

void Player::Update(float dt)
{
	ProcessInput(dt);
	shape.setPosition(position);
}

void Player::ProcessInput(float dt)
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


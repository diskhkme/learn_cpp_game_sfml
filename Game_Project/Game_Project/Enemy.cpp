#include "Game.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(Game* game, ActorType type, const sf::Vector2f pos, float size, float speed) // dependency injection
	: Actor{ game, type, pos, speed, size }
{
	shape.setTexture(this->game->GetShipTexture());
	shape.setTextureRect(sf::IntRect{ 40,0,8,8 });

	shape.setScale(sf::Vector2f{ size,size });
	sf::FloatRect bounds = shape.getLocalBounds();
	shape.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

Enemy::Enemy()
	: Enemy{nullptr, ActorType::ENEMY, sf::Vector2f{0,0}, 1.0f, 1.0f }
{}

Enemy::~Enemy()
{
}


void Enemy::Update(float dt)
{
	if (isActive)
	{
		UpdatePosition(dt);
		shape.setPosition(position);
	}
}

void Enemy::UpdatePosition(float dt)
{
	sf::Vector2f playerPosition = game->GetPlayer()->getPosition();

	sf::Vector2f enemyToPlayer = playerPosition - position;

	float length = sqrt(enemyToPlayer.x * enemyToPlayer.x + enemyToPlayer.y * enemyToPlayer.y);

	enemyToPlayer /= length;

	position += enemyToPlayer * speed * dt;
}

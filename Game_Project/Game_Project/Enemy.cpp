#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(const sf::Vector2f pos, float size, sf::Color color, float speed,
	const Player* player) // dependency injection
	: position{ pos }, size{ size }, color{ color }, speed{ speed }, playerRef{ player }
{
	shape = sf::CircleShape{ size };
	shape.setFillColor(color);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(1.0f);
}

Enemy::Enemy()
	: Enemy{ sf::Vector2f{0,0}, 1.0f, sf::Color{255,255,0,255}, 1.0f, nullptr }
{}


void Enemy::Update(float dt)
{
	UpdatePosition(dt);
	shape.setPosition(position);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}

void Enemy::UpdatePosition(float dt)
{
	sf::Vector2f playerPosition = playerRef->getPosition();

	sf::Vector2f enemyToPlayer = playerPosition - position;

	float length = sqrt(enemyToPlayer.x * enemyToPlayer.x + enemyToPlayer.y * enemyToPlayer.y);

	enemyToPlayer /= length;

	position += enemyToPlayer * speed * dt;
}

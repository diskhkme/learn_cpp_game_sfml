#include "Game.h"
#include "Enemy.h"
#include "Player.h"

Enemy::Enemy(Game* game, const sf::Vector2f pos, float size, sf::Color color, float speed) // dependency injection
	: position{ pos }, size{ size }, color{ color }, speed{ speed }, game{game}
{
	shape = sf::CircleShape{ size };
	shape.setFillColor(color);
	shape.setOutlineColor(sf::Color::Red);
	shape.setOutlineThickness(1.0f);
}

Enemy::Enemy()
	: Enemy{nullptr, sf::Vector2f{0,0}, 1.0f, sf::Color{255,255,0,255}, 1.0f }
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
	sf::Vector2f playerPosition = game->GetPlayer()->getPosition();

	sf::Vector2f enemyToPlayer = playerPosition - position;

	float length = sqrt(enemyToPlayer.x * enemyToPlayer.x + enemyToPlayer.y * enemyToPlayer.y);

	enemyToPlayer /= length;

	position += enemyToPlayer * speed * dt;
}

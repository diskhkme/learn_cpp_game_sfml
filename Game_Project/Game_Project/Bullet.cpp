#include "Bullet.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"


Bullet::Bullet(Game* game, float size, const sf::Color& color, float speed)
	: size{ size }, color{ color }, speed{ speed }, game{game}
{
	Player* player = this->game->GetPlayer();
	position = player->getPosition();

	direction = GetPlayerToClosestEnemyVector();

	shape = sf::CircleShape{ size };
	shape.setFillColor(color);
	shape.setOutlineColor(sf::Color::Green);
	shape.setOutlineThickness(0.3f);
}

Bullet::Bullet()
	: Bullet{nullptr, 0.3f, sf::Color{255,255,0,255}, 5.0f }
{}

void Bullet::Update(float dt)
{
	UpdatePosition(dt);
	shape.setPosition(position);
}

void Bullet::Draw(sf::RenderWindow& window)
{
	window.draw(shape);
}


void Bullet::UpdatePosition(float dt)
{
	position += direction * speed * dt;
	shape.setPosition(position);
}

sf::Vector2f Bullet::GetPlayerToClosestEnemyVector()
{
	Player* player = this->game->GetPlayer();
	std::vector<Enemy*> enemies = this->game->GetEnemies();

	sf::Vector2f playerPos = player->getPosition();

	float minDist = 10000.0f;
	sf::Vector2f minDistVec = sf::Vector2f{ 1.0f, 0.0f };

	for (int i = 0; i < enemies.size(); i++)
	{
		sf::Vector2f enemyPos = enemies[i]->getPosition();
		
		sf::Vector2f playerToEnemyVec = enemyPos - playerPos;
		float dist = sqrt(playerToEnemyVec.x * playerToEnemyVec.x + playerToEnemyVec.y * playerToEnemyVec.y);

		if (dist < minDist)
		{
			minDist = dist;
			minDistVec = playerToEnemyVec / dist;
		}
	}

	return minDistVec;
}

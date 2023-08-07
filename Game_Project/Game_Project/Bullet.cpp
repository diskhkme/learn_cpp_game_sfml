#include "Bullet.h"
#include "Game.h"
#include "Player.h"
#include "Enemy.h"


Bullet::Bullet(Game* game, float size, float speed)
	: Actor{ game, game->GetPlayer()->getPosition(), speed, size }
{
	direction = GetPlayerToClosestEnemyVector();

	shape.setTexture(this->game->GetProjectileTexture());
	shape.setTextureRect(sf::IntRect{ 0,0,8,8 });

	shape.setScale(sf::Vector2f{ size,size });
	sf::FloatRect bounds = shape.getLocalBounds();
	shape.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
}

Bullet::Bullet()
	: Bullet{nullptr, 0.3f, 5.0f }
{}

void Bullet::Update(float dt)
{
	UpdatePosition(dt);
	shape.setPosition(position);
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

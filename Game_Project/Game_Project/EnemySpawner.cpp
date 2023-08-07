#include "EnemySpawner.h"
#include "Game.h"
#include "Enemy.h"

EnemySpawner::EnemySpawner(Game* game, float spawnPeriod)
	: game{game}, spawnPeriod{spawnPeriod},
	spawnTimer{ spawnPeriod }
{
}

void EnemySpawner::SetEnemyData(float size, float speed)
{
	this->enemySize = size;
	this->enemySpeed = speed;
}

void EnemySpawner::Update(float dt)
{
	spawnTimer -= dt;
	if (spawnTimer < 0.0f)
	{
		spawnTimer = spawnPeriod;
		sf::Vector2f randomPos = SampleRandomSpawnPoisition();
		game->GetActors().emplace_back(new Enemy{ game, ActorType::ENEMY, randomPos, enemySize, enemySpeed });
	}
}

sf::Vector2f EnemySpawner::SampleRandomSpawnPoisition()
{
	sf::Vector2i screenSize = game->GetScreenSize();

	// 화면 밖 random spawn position random 선정
	SpawnDirection spawnDir = (SpawnDirection)(rand() % 4);
	if (spawnDir == EAST || spawnDir == WEST)
	{
		float randVertPos = (float)(rand() % screenSize.y);
		if (spawnDir == EAST)
		{
			return sf::Vector2f{ (float)screenSize.x + 10.0f, randVertPos };
		}
		else
		{
			return sf::Vector2f{ -10.0f, randVertPos };
		}
	}
	else
	{
		float randHorPos = (float)(rand() % screenSize.y);
		if (spawnDir == SOUTH)
		{
			return sf::Vector2f{ randHorPos, (float)screenSize.y + 10.0f };
		}
		else
		{
			return sf::Vector2f{ randHorPos, -10.0f };
		}
	}
}

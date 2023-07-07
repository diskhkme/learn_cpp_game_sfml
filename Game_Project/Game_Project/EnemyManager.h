#pragma once

#include "Enemy.h"

class EnemyManager
{
public:
	enum SpawnDirection
	{
		EAST, WEST, SOUTH, NORTH
	};

	EnemyManager(Game* game)
		: game{game}
	{
		spawnRate = game->GetEnemySpawnRate();
		currentEnemyCount = 0;
		spawnTimer = 0.0f;
		screenWidth = game->GetScreenSize().x;
		screenHeight = game->GetScreenSize().y;

		// default 값
		enemySize = 10.0f;
		enemySpeed = 100.0f;
		enemies = game->GetEnemies();
	}

	void SetEnemyData(float size, const sf::Color& color, float speed)
	{
		this->enemySize = size;
		this->enemySpeed = speed;
	}

	int GetCurrentEnemyCount() { return currentEnemyCount; }

	// 임시. Actor 상속 후엔 바꿀 것
	void Update(float dt)
	{
		spawnTimer -= dt;
		if (spawnTimer < 0.0f)
		{
			spawnTimer = spawnRate;
			enemies[currentEnemyCount] = Enemy{ game, GetRandomSpawnPosition() };
			currentEnemyCount++;
		}

		for (int i = 0; i < currentEnemyCount; i++)
		{
			enemies[i].Update(dt);
		}
	}

	void Draw(sf::RenderWindow& window)
	{
		for (int i = 0; i < currentEnemyCount; i++)
		{
			enemies[i].Draw(window);
		}
	}
private:
	sf::Vector2f GetRandomSpawnPosition()
	{
		// 화면 밖 random spawn position random 선정
		SpawnDirection spawnDir = (SpawnDirection)(rand() % 4);
		if (spawnDir == EAST || spawnDir == WEST)
		{
			float randVertPos = (float)(rand() % screenHeight);
			if (spawnDir == EAST)
			{
				return sf::Vector2f{ (float)screenWidth + 10.0f, randVertPos };
			}
			else
			{
				return sf::Vector2f{ -10.0f, randVertPos };
			}
		}
		else
		{
			float randHorPos = (float)(rand() % screenWidth);
			if (spawnDir == SOUTH)
			{
				return sf::Vector2f{ randHorPos, (float)screenHeight + 10.0f };
			}
			else
			{
				return sf::Vector2f{ randHorPos, - 10.0f };
			}
		}

	}

private:
	Game* game;
	Enemy* enemies;

	int maxEnemy;
	int currentEnemyCount;
	float spawnRate;
	float spawnTimer;
	int screenWidth;
	int screenHeight;

	float enemySize;
	float enemySpeed;

};
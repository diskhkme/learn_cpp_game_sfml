#pragma once

#include <SFML/Graphics.hpp>

class Game;

class EnemySpawner
{
public:
	enum SpawnDirection
	{
		EAST, WEST, SOUTH, NORTH
	};

	EnemySpawner(Game* game, float spawnPeriod);

	void SetEnemyData(float size, float speed);

	void Update(float dt);

private:
	sf::Vector2f SampleRandomSpawnPoisition();

private:
	Game* game;
	
	float spawnPeriod;
	float spawnTimer;
	int screenWidth;
	int screenHeight;

	float enemySize;
	float enemySpeed;
};

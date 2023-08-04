#pragma once

#include <SFML/Graphics.hpp>

class Player;
class Enemy;
class Bullet;
class Weapon;

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();

	void Shutdown();

private:
	void InitializeGame();

	void ProcessInput();

	void UpdateGame();

	void DrawGame();

private:
	int screenWidth = 800;
	int screenHeight = 450;
	sf::RenderWindow window{ sf::VideoMode(screenWidth, screenHeight), "CPP Game" };

	const int maxEnemyCount = 50;
	const int maxBulletCount = 50;

	Player* player;
	Enemy* enemies;
	Bullet* bullets;
	Weapon* weapon;

	sf::Clock deltaClock;
};
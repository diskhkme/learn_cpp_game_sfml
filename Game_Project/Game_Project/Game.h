#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Player;
class Enemy;
class Bullet;

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();

	void Shutdown();

	Player* GetPlayer() { return player; }
	std::vector<Enemy*> GetEnemies() { return enemies; }
	std::vector<Bullet*> GetBullets() { return bullets; }

private:
	void InitializeGame();

	void ProcessInput();

	void UpdateGame();

	void DrawGame();

private:
	int screenWidth = 800;
	int screenHeight = 450;
	sf::RenderWindow window{ sf::VideoMode(screenWidth, screenHeight), "CPP Game" };

	Player* player;
	std::vector<Enemy*> enemies;
	std::vector<Bullet*> bullets;

	float bulletFirePeriod;
	float bulletFireTimer;
	sf::Color enemyColor;
	sf::Color bulletColor;

	sf::Clock deltaClock;
};
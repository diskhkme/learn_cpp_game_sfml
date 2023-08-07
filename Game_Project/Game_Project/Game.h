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

	sf::Texture& GetShipTexture() { return shipsTexture; }
	sf::Texture& GetProjectileTexture() { return projectilTexture; }

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

	sf::Texture shipsTexture;
	sf::Texture projectilTexture;

	float bulletFirePeriod;
	float bulletFireTimer;

	sf::Clock deltaClock;
};
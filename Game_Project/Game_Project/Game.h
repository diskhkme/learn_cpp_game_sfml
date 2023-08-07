#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Player;
class Enemy;
class Bullet;
class Actor;
class EnemySpawner;

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();

	void Shutdown();

	Player* GetPlayer() { return player; }
	std::vector<Actor*>& GetActors() { return actors; }

	sf::Texture& GetShipTexture() { return shipsTexture; }
	sf::Texture& GetProjectileTexture() { return projectilTexture; }

	sf::Vector2i GetScreenSize() { return sf::Vector2i{screenWidth, screenHeight}; }

private:
	void InitializeGame();

	void ProcessInput();

	void UpdateGame();
	void SpawnBullet(float dt);
	void CheckCollision();

	void DrawGame();

private:
	int screenWidth = 800;
	int screenHeight = 450;
	sf::RenderWindow window{ sf::VideoMode(screenWidth, screenHeight), "CPP Game" };

	std::vector<Actor*> actors;
	
	Player* player;

	EnemySpawner* enemySpawner;

	sf::Texture shipsTexture;
	sf::Texture projectilTexture;
	sf::Texture backgroundTexture;
	sf::Font font;

	sf::Sprite backgroundShape;

	float bulletFirePeriod;
	float bulletFireTimer;

	int score;
	sf::Text scoreText;

	bool gameOver;
	sf::Text gameOverText;

	sf::Clock deltaClock;
};
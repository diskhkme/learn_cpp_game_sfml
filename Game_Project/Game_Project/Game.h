#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

class Player;
class Enemy;
class Bullet;
class Actor;

class Game
{
public:
	Game();
	bool Initialize();
	void RunLoop();

	void Shutdown();

	Player* GetPlayer() { return player; }
	std::vector<Actor*> GetActors() { return actors; }

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

	std::vector<Actor*> actors;
	
	Player* player;

	sf::Texture shipsTexture;
	sf::Texture projectilTexture;

	float bulletFirePeriod;
	float bulletFireTimer;

	sf::Clock deltaClock;
};
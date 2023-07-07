#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Weapon.h"
#include "EnemyManager.h"

class Game
{
public:
	Game()
		: player{nullptr}, enemies{nullptr}, enemyManager{nullptr},
		bullets{nullptr}, weapon{nullptr}
	{

	}
	bool Initialize()
	{
		// Initialize SFML System

		// Initialize Game
		InitializeGame();

		return true;
	}
	void RunLoop()
	{
		while (window.isOpen())
		{
			ProcessInput();
			UpdateGame();
			Draw();
		}
	}

	void Shutdown()
	{
		delete player;
		delete[] enemies;
		delete enemyManager;
		delete[] bullets;
		delete weapon;
	}

private:
	void InitializeGame()
	{
		// Player
		player = new Player{ sf::Vector2f{screenWidth / 2.0f, screenHeight / 2.0f}, 20.0f, sf::Color{238,108,77,255}, 200.0f };

		// Enemies
		const int maxEnemyCount = 50;
		enemies = new Enemy[maxEnemyCount];
		enemyManager = new EnemyManager{ player, enemies, maxEnemyCount, 1.5f, screenWidth, screenHeight };

		// Weapon (Bullet »ý¼º)
		const int maxBullet = 50;
		bullets = new Bullet[maxBullet];
		weapon = new Weapon{ bullets, maxBullet, player, 1.0f, enemies, maxEnemyCount };

	}

	void ProcessInput()
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		}
	}

	void UpdateGame()
	{
		float dt = deltaClock.restart().asSeconds();

		// Logic Update
		player->Update(dt);
		enemyManager->Update(dt);
		weapon->Update(dt);
	}

	void Draw()
	{
		window.clear();
		{
			player->Draw(window);

			enemyManager->Draw(window);

			weapon->Draw(window);

		}
		window.display();
	}

private:
	int screenWidth = 800;
	int screenHeight = 450;
	sf::RenderWindow window{ sf::VideoMode(screenWidth, screenHeight), "CPP Game" };

	Player* player;
	Enemy* enemies;
	EnemyManager* enemyManager;
	Bullet* bullets;
	Weapon* weapon;

	sf::Clock deltaClock;
};
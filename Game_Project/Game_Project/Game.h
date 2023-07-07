#pragma once

#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Weapon.h"
#include "EnemyManager.h"
#include "Enemy.h"
#include "Bullet.h"

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
		// Initialize Resources
		if (!shipsTexture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Ships.png"))
		{
			return false;
		}

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

	sf::Texture& GetShipTexture() { return shipsTexture; }
	sf::Vector2i GetScreenSize() { return sf::Vector2i{screenWidth,screenHeight}; }
	Enemy* GetEnemies() { return enemies; }
	Bullet* GetBullets() { return bullets; }
	Player* GetPlayer() { return player; }

	float GetEnemySpawnRate() { return enemySpawnRate; }
	float GetBulletFireRate() { return bulletFireRate; }

private:
	void InitializeGame()
	{
		// Player (Init을 Player 생성자 내부 로직으로 전부 변경)
		sf::Vector2f playerInitPos = sf::Vector2f{ screenWidth/2.0f, screenHeight / 2.0f };
		player = new Player{ this, playerInitPos };

		// Enemies
		const int maxEnemyCount = 50;
		enemies = new Enemy[maxEnemyCount];
		enemyManager = new EnemyManager{ this };

		// Weapon (Bullet 생성)
		const int maxBullet = 50;
		bullets = new Bullet[maxBullet];
		weapon = new Weapon{ this };

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
	// Window
	int screenWidth = 800;
	int screenHeight = 450;
	sf::RenderWindow window{ sf::VideoMode(screenWidth, screenHeight), "CPP Game" };

	// Resources
	sf::Texture shipsTexture;

	// Game data
	Player* player;
	Enemy* enemies;
	EnemyManager* enemyManager;
	Bullet* bullets;
	Weapon* weapon;

	float bulletFireRate;
	float enemySpawnRate;

	sf::Clock deltaClock;
};
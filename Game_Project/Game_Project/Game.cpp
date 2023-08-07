#include "Game.h"

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

Game::Game()
	: player{ nullptr }
{
	enemies.clear();
	bullets.clear();
}
bool Game::Initialize()
{
	// Initialize SFML System

	// Initialize Resources
	if (!shipsTexture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Ships.png"))
	{
		return false;
	}
	if (!projectilTexture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_Projectiles.png"))
	{
		return false;
	}

	// Initialize Game
	InitializeGame();

	return true;
}
void Game::RunLoop()
{
	while (window.isOpen())
	{
		ProcessInput();
		UpdateGame();
		DrawGame();
	}
}

void Game::Shutdown()
{
	delete player;
	for (int i = 0; i < bullets.size(); i++)
	{
		delete bullets[i];
	}
	for (int i = 0; i < enemies.size(); i++)
	{
		delete enemies[i];
	}
}

void Game::InitializeGame()
{
	// Player
	player = new Player{ this, sf::Vector2f{screenWidth / 2.0f, screenHeight / 2.0f}, 3.0f, 200.0f };

	// Enemies
	for (int i = 0; i < 10; i++)
	{
		sf::Vector2f enemyInitPosition = sf::Vector2f{ (float)(screenWidth - 100) , (float)(rand() % screenHeight) };
		enemies.emplace_back(new Enemy{this, enemyInitPosition , 3.0f, 100.0f });
	}

	// Weapon (Bullet »ý¼º)
	bulletFirePeriod = 1.0f;
	bulletFireTimer = bulletFirePeriod;

}

void Game::ProcessInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();
	}
}

void Game::UpdateGame()
{
	float dt = deltaClock.restart().asSeconds();

	// Logic Update
	bulletFireTimer -= dt;
	if (bulletFireTimer < 0.0f)
	{
		bulletFireTimer = bulletFirePeriod;
		bullets.emplace_back(new Bullet{ this, 3.0f,  500.0f });
	}

	player->Update(dt);
	for (int i = 0; i < enemies.size(); i++)
	{
		enemies[i]->Update(dt);
	}
	for (int i = 0; i < bullets.size(); i++)
	{
		bullets[i]->Update(dt);
	}

}

void Game::DrawGame()
{
	window.clear();
	{
		player->Draw(window);

		for (int i = 0; i < enemies.size(); i++)
		{
			enemies[i]->Draw(window);
		}
		for (int i = 0; i < bullets.size(); i++)
		{
			bullets[i]->Draw(window);
		}

	}
	window.display();
}
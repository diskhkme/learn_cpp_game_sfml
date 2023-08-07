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
	player = new Player{ sf::Vector2f{screenWidth / 2.0f, screenHeight / 2.0f}, 20.0f, sf::Color{238,108,77,255}, 200.0f };

	// Enemies
	enemyColor = sf::Color{ 200, 150, 255, 255 };

	for (int i = 0; i < 10; i++)
	{
		sf::Vector2f enemyInitPosition = sf::Vector2f{ (float)(screenWidth - 100) , (float)(rand() % screenHeight) };
		enemies.emplace_back(new Enemy{this, enemyInitPosition , 10.0f, enemyColor, 100.0f });
	}

	// Weapon (Bullet »ý¼º)
	bulletColor = sf::Color{ 0, 255, 0, 255 };
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
		bullets.emplace_back(new Bullet{ this, 3.0f, bulletColor,  500.0f });
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
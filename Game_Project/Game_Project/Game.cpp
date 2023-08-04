#include "Game.h"

#include "Player.h"
#include "Weapon.h"
#include "Enemy.h"
#include "Bullet.h"

Game::Game()
	: player{ nullptr }, enemies{ nullptr },
	bullets{ nullptr }, weapon{ nullptr }
{

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
	delete[] enemies;
	delete[] bullets;
	delete weapon;
}

void Game::InitializeGame()
{
	// Player
	player = new Player{ sf::Vector2f{screenWidth / 2.0f, screenHeight / 2.0f}, 20.0f, sf::Color{238,108,77,255}, 200.0f };

	// Enemies
	enemies = new Enemy[maxEnemyCount];
	const sf::Color enemyColor = sf::Color{ 200, 150, 255, 255 };
	for (int i = 0; i < maxEnemyCount; i++)
	{
		sf::Vector2f enemyInitPosition = sf::Vector2f{ (float)(screenWidth - 100) , (float)(rand() % screenHeight) };
		enemies[i] = Enemy{ enemyInitPosition , 10.0f, enemyColor, 100.0f, player };
	}

	// Weapon (Bullet »ý¼º)
	bullets = new Bullet[maxBulletCount];
	weapon = new Weapon{ bullets, player, 1.0f, maxBulletCount, enemies, maxEnemyCount };

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
	weapon->SpawnBullet(dt);

	player->Update(dt);
	for (int i = 0; i < maxEnemyCount; i++)
	{
		enemies[i].Update(dt);
	}
	for (int i = 0; i < weapon->GetCurrentBulletCount(); i++)
	{
		bullets[i].Update(dt);
	}
	
}

void Game::DrawGame()
{
	window.clear();
	{
		player->Draw(window);

		for (int i = 0; i < maxEnemyCount; i++)
		{
			enemies[i].Draw(window);
		}
		for (int i = 0; i < weapon->GetCurrentBulletCount(); i++)
		{
			bullets[i].Draw(window);
		}

	}
	window.display();
}

#include "Game.h"

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

Game::Game()
	: player{ nullptr }, bulletFirePeriod{0.0}, bulletFireTimer{0.0}
{
	enemies.clear();
	bullets.clear();

	actors.clear();
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
	for (int i = 0; i < actors.size(); i++)
	{
		delete actors[i];
	}
}

void Game::InitializeGame()
{
	// Player
	player = new Player{ this, sf::Vector2f{screenWidth / 2.0f, screenHeight / 2.0f}, 3.0f, 200.0f };
	actors.push_back(player);

	// Enemies
	for (int i = 0; i < 10; i++)
	{
		sf::Vector2f enemyInitPosition = sf::Vector2f{ (float)(screenWidth - 100) , (float)(rand() % screenHeight) };
		actors.emplace_back(new Enemy{ this, enemyInitPosition , 3.0f, 100.0f });
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
		actors.emplace_back(new Bullet{ this, 3.0f,  500.0f });
	}

	for (int i = 0; i < actors.size(); i++)
	{
		actors[i]->Update(dt);
	}

}

void Game::DrawGame()
{
	window.clear();
	{
		for (int i = 0; i < actors.size(); i++)
		{
			actors[i]->Draw(window);
		}
	}
	window.display();
}
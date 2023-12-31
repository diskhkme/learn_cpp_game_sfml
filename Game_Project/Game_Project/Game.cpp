﻿#include "Game.h"

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "EnemySpawner.h"

Game::Game()
	: player{ nullptr }, bulletFirePeriod{ 0.0 }, bulletFireTimer{ 0.0 }, score{ 0 }, gameOver{ false }
{
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
	if (!backgroundTexture.loadFromFile("../resources/sprites/SpaceShooterAssetPack_BackGrounds.png"))
	{
		return false;
	}
	if (!font.loadFromFile("../resources/font/arial.ttf"))
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

	delete enemySpawner;

	actors.clear();
}

void Game::InitializeGame()
{
	// Player
	player = new Player{ this, ActorType::PLAYER, sf::Vector2f{screenWidth / 2.0f, screenHeight / 2.0f}, 3.0f, 200.0f };
	actors.push_back(player);

	// Enemiy Spawner
	enemySpawner = new EnemySpawner{ this, 1.0f };
	enemySpawner->SetEnemyData(3.0f, 180.0f);

	// Weapon (Bullet »ý¼º)
	bulletFirePeriod = 2.0f;
	bulletFireTimer = bulletFirePeriod;

	// Background
	backgroundShape.setTexture(backgroundTexture);
	backgroundShape.setTextureRect(sf::IntRect{ 0,0,128,256 });

	backgroundShape.setScale(sf::Vector2f{ 3.0,3.0 });
	sf::FloatRect bounds = backgroundShape.getLocalBounds();
	backgroundShape.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	backgroundShape.setPosition(sf::Vector2f{ (float)screenWidth / 2, (float)screenHeight / 2 });
	backgroundShape.setRotation(90.0f);

	// Score Text
	scoreText.setFont(font);
	scoreText.setCharacterSize(24);
	scoreText.setFillColor(sf::Color::White);

	// GameOver Text
	gameOverText.setFont(font);
	gameOverText.setCharacterSize(48);
	gameOverText.setFillColor(sf::Color::White);
}

void Game::ProcessInput()
{
	sf::Event event;
	while (window.pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
			window.close();

		if (gameOver && event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::R)
		{
			gameOver = false;
			score = 0;

			Shutdown();
			InitializeGame();
			
		}
	}
}

void Game::UpdateGame()
{
	float dt = deltaClock.restart().asSeconds();

	// Logic Update
	if (!gameOver)
	{
		SpawnBullet(dt);
		enemySpawner->Update(dt);

		for (int i = 0; i < actors.size(); i++)
		{
			actors[i]->Update(dt);
		}

		CheckCollision();
	}
	

}

void Game::SpawnBullet(float dt)
{
	bulletFireTimer -= dt;
	if (bulletFireTimer < 0.0f)
	{
		bulletFireTimer = bulletFirePeriod;
		actors.emplace_back(new Bullet{ this, ActorType::BULLET, 3.0f,  500.0f });
	}
}

void Game::CheckCollision()
{
	// Bullet - Enemy Collision
	for (int i = 0; i < actors.size(); i++)
	{
		for (int j = 0; j < actors.size(); j++)
		{
			if (actors[i]->GetIsActive() == false || actors[j]->GetIsActive() == false)
				continue;

			if (actors[i]->GetActorType() == ActorType::BULLET && actors[j]->GetActorType() == ActorType::ENEMY)
			{
				sf::Vector2f bulletPos = actors[i]->getPosition();
				sf::Vector2f enemyPos = actors[j]->getPosition();

				sf::Vector2f bulletToEnemyPos = bulletPos - enemyPos;
				float dist = sqrt(bulletToEnemyPos.x * bulletToEnemyPos.x + bulletToEnemyPos.y * bulletToEnemyPos.y);

				if (dist < 5.0f)
				{
					actors[i]->SetIsActive(false);
					actors[j]->SetIsActive(false);
					score++;
				}
			}

		}
	}

	// Player - Enemy Collision
	for (int i = 0; i < actors.size(); i++)
	{
		if (actors[i]->GetIsActive() == false)
			continue;

		if (actors[i]->GetActorType() == ActorType::ENEMY)
		{
			sf::Vector2f playerPos = player->getPosition();
			sf::Vector2f enemyPos = actors[i]->getPosition();

			sf::Vector2f enemyToPlayerPos = enemyPos - playerPos;
			float dist = sqrt(enemyToPlayerPos.x * enemyToPlayerPos.x + enemyToPlayerPos.y * enemyToPlayerPos.y);

			if (dist < 5.0f)
			{
				gameOver = true;
			}
		}
	}
}

void Game::DrawGame()
{
	window.clear();
	{
		// draw backgrounds
		window.draw(backgroundShape);

		// draw actors
		for (int i = 0; i < actors.size(); i++)
		{
			actors[i]->Draw(window);
		}

		// draw score
		scoreText.setString("Score : " + std::to_string(score));
		window.draw(scoreText);

		if (gameOver)
		{
			gameOverText.setString("Game Over\n Press R to restart the game");
			window.draw(gameOverText);
		}
	}
	window.display();
}

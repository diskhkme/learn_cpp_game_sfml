#include "Game.h"

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

Game::Game()
	: player{ nullptr }, bulletFirePeriod{0.0}, bulletFireTimer{0.0}
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
	player = new Player{ this, ActorType::PLAYER, sf::Vector2f{screenWidth / 2.0f, screenHeight / 2.0f}, 3.0f, 200.0f };
	actors.push_back(player);

	// Enemies
	for (int i = 0; i < 10; i++)
	{
		sf::Vector2f enemyInitPosition = sf::Vector2f{ (float)(screenWidth - 100) , (float)(rand() % screenHeight) };
		actors.emplace_back(new Enemy{ this, ActorType::ENEMY, enemyInitPosition , 3.0f, 100.0f });
	}

	// Weapon (Bullet »ý¼º)
	bulletFirePeriod = 1.0f;
	bulletFireTimer = bulletFirePeriod;

	// Background
	backgroundShape.setTexture(backgroundTexture);
	backgroundShape.setTextureRect(sf::IntRect{ 0,0,128,256 });

	backgroundShape.setScale(sf::Vector2f{ 3.0,3.0 });
	sf::FloatRect bounds = backgroundShape.getLocalBounds();
	backgroundShape.setOrigin(std::floor(bounds.left + bounds.width / 2.f), std::floor(bounds.top + bounds.height / 2.f));
	backgroundShape.setPosition(sf::Vector2f{ (float)screenWidth / 2, (float)screenHeight / 2 });
	backgroundShape.setRotation(90.0f);
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
	SpawnBullet(dt);

	for (int i = 0; i < actors.size(); i++)
	{
		actors[i]->Update(dt);
	}

	CheckCollision();

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
				}
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


		for (int i = 0; i < actors.size(); i++)
		{
			actors[i]->Draw(window);
		}
	}
	window.display();
}
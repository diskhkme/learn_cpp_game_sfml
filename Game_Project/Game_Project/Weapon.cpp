#include "Weapon.h"
#include "Bullet.h"
#include "Player.h"
#include "Enemy.h"
#include "MathUtil.h"

Weapon::Weapon(Bullet* bullets, const Player& player, float fireRate, int maxBulletCount, const Enemy* const enemies, int enemyCount)
	: bullets{ bullets }, playerRef{player}, fireRate{ fireRate }, bulletMaxCount{ maxBulletCount },
	enemies{enemies}, enemyCount{enemyCount}
{
	currentBulletCount = 0;
	bulletFireTimer = fireRate;

	// default °ª
	bulletSize = 3.0f;
	bulletColor = sf::Color{ 0, 255, 0, 255 };
	bulletSpeed = 500.0f;
}

void Weapon::SetBulletData(float size, const sf::Color& color, float speed)
{
	this->bulletSize = size;
	this->bulletColor = color;
	this->bulletSpeed = speed;
}

// ÀÓ½Ã. Actor »ó¼Ó ÈÄ¿£ ¹Ù²Ü °Í
void Weapon::SpawnBullet(float dt)
{
	bulletFireTimer -= dt;
	if (bulletFireTimer < 0.0f)
	{
		bulletFireTimer = fireRate;
		bullets[currentBulletCount] = Bullet{ playerRef.getPosition(), CalculateShootDirection(), bulletSize, bulletColor, bulletSpeed};
		currentBulletCount++;
	}
}

sf::Vector2f Weapon::CalculateShootDirection()
{
	float minLength = 10000.0f;
	int minEnemyInd = 0;
	for (int i = 0; i < enemyCount; i++)
	{
		float length = GetLength(playerRef.getPosition() - enemies[i].getPosition());
		if (length < minLength)
		{
			minLength = length;
			minEnemyInd = i;
		}
	}

	sf::Vector2f shootDir = GetNormalizedVector(enemies[minEnemyInd].getPosition() - playerRef.getPosition());

	return shootDir;
}


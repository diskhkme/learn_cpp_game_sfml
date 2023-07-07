#pragma once

#include "Bullet.h"
#include "Player.h"
#include "MathUtil.h"

class Weapon
{
public:
    Weapon(Bullet* bullets, int maxCount, const Player& player, float fireRate,  const Enemy* const enemies, int enemyCount)
        : bullets{ bullets }, playerRef { player }, fireRate{ fireRate }, bulletMaxCount{ maxCount }, enemies{ enemies }, enemyCount{ enemyCount }
    {
        currentBulletCount = 0;
        bulletFireTimer = fireRate;

        // default 값
        bulletSize = 3.0f;
        bulletColor = sf::Color{ 0, 255, 0, 255 };
        bulletSpeed = 500.0f;
    }

    void SetBulletData(float size, const sf::Color& color, float speed)
    {
        this->bulletSize = size;
        this->bulletColor = color;
        this->bulletSpeed = speed;
    }

    // 임시. Actor 상속 후엔 바꿀 것
    void Update(float dt)
    {
        bulletFireTimer -= dt;
        if (bulletFireTimer < 0.0f)
        {
            bulletFireTimer = fireRate;
            bullets[currentBulletCount] = Bullet{ playerRef.getPosition(), GetShootDirection(), bulletSize, bulletColor, bulletSpeed};
            currentBulletCount++;
        }

        for (int i = 0; i < currentBulletCount; i++)
        {
            bullets[i].Update(dt);
        }
    }

    void Draw(sf::RenderWindow& window)
    {
        for (int i = 0; i < currentBulletCount; i++)
        {
            bullets[i].Draw(window);
        }
    }
private:
    sf::Vector2f GetShootDirection()
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

private:
    const Player& playerRef;
    float fireRate;
    const Enemy* const enemies;
    int enemyCount;

    float bulletSize;
    sf::Color bulletColor;
    float bulletSpeed;

    Bullet* bullets;
    int bulletMaxCount;
    int currentBulletCount;
    float bulletFireTimer;
};
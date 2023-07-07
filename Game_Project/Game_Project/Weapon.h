#pragma once

#include "Bullet.h"
#include "Player.h"
#include "MathUtil.h"
#include "Enemy.h"

class Weapon
{
public:
    Weapon(Game* game)
        : game{game}
    {
        bullets = game->GetBullets();
        enemies = game->GetEnemies();

        currentBulletCount = 0;
        bulletFireTimer = fireRate;

        // default 값
        bulletSize = 3.0f;
        bulletSpeed = 500.0f;
    }

    void SetBulletData(float size, const sf::Color& color, float speed)
    {
        this->bulletSize = size;
        this->bulletSpeed = speed;
    }

    int GetCurrentBulletCount() { return currentBulletCount; }

    // 임시. Actor 상속 후엔 바꿀 것
    void Update(float dt)
    {
        bulletFireTimer -= dt;
        if (bulletFireTimer < 0.0f)
        {
            bulletFireTimer = fireRate;
            bullets[currentBulletCount] = Bullet{ game, game->GetPlayer()->getPosition(), GetShootDirection()};
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
            float length = GetLength(game->GetPlayer()->getPosition() - enemies[i].getPosition());
            if (length < minLength)
            {
                minLength = length;
                minEnemyInd = i;
            }
        }

        sf::Vector2f shootDir = GetNormalizedVector(enemies[minEnemyInd].getPosition() - game->GetPlayer()->getPosition());

        return shootDir;
    }

private:
    Game* game;
    Bullet* bullets;
    Enemy* enemies;

    float fireRate;
    int enemyCount;

    float bulletSize;
    float bulletSpeed;

    int bulletMaxCount;
    int currentBulletCount;
    float bulletFireTimer;
};
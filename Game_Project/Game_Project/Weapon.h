#pragma once

#include "Bullet.h"
#include "Player.h"

class Weapon
{
public:
    Weapon(const Player& player, float fireRate, int maxCount)
        : playerRef{ player }, fireRate{ fireRate }, bulletMaxCount{maxCount}
    {
        bullets = new Bullet[bulletMaxCount];
        currentBulletCount = 0;
        bulletFireTimer = fireRate;

        // default 값
        bulletSize = 3.0f;
        bulletColor = sf::Color{ 0, 255, 0, 255 };
        bulletSpeed = 500.0f;
    }

    ~Weapon()
    {
        delete[] bullets;
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
            bullets[currentBulletCount] = Bullet{ playerRef.getPosition(), sf::Vector2f{1.0f, 0.0f}, bulletSize, bulletColor, bulletSpeed};
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
    const Player& playerRef;
    float fireRate;

    float bulletSize;
    sf::Color bulletColor;
    float bulletSpeed;

    int bulletMaxCount;
    Bullet* bullets;
    int currentBulletCount;
    float bulletFireTimer;
};
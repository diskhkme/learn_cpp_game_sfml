#pragma once

#include <SFML/Graphics.hpp>

class Bullet;
class Player;
class Enemy;

class Weapon
{
public:
    Weapon(Bullet* bullets, const Player* const player, float fireRate, int maxBulletCount, const Enemy* const enemies, int enemyCount);

    void SetBulletData(float size, const sf::Color& color, float speed);

    void SpawnBullet(float dt);

    int GetCurrentBulletCount() { return currentBulletCount; }

private:
    sf::Vector2f CalculateShootDirection();

private:
    const Player* const playerRef;
    float fireRate;

    float bulletSize;
    sf::Color bulletColor;
    float bulletSpeed;

    int bulletMaxCount;
    Bullet* bullets;
    int currentBulletCount;
    float bulletFireTimer;

    const Enemy* const enemies;
    int enemyCount;
};
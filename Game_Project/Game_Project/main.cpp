#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif


#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

int main()
{
    _CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
    //_CrtSetBreakAlloc(2508); // 누수가 있는 경우 할당 번호로 중단 설정

    {
        int screenWidth = 800;
        int screenHeight = 450;

        sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "05_Enemies_Movement");
        window.setFramerateLimit(60);

        // Player
        Player player = Player{ sf::Vector2f{10.0f, 10.0f}, 20.0f, sf::Color{238,108,77,255}, 200.0f };

        // Enemies
        const int enemyCount = 10;
        Enemy* enemies = new Enemy[enemyCount];
        const sf::Color enemyColor = sf::Color{ 200, 150, 255, 255 };
        for (int i = 0; i < enemyCount; i++)
        {
            sf::Vector2f enemyInitPosition = sf::Vector2f{ (float)(screenWidth - 100) , (float)(rand() % screenHeight) };
            enemies[i] = Enemy{ enemyInitPosition , 10.0f, enemyColor, 100.0f, &player };
        }

        // Bullets
        const int bulletCount = 50;
        Bullet* bullets = new Bullet[bulletCount];
        int currentBulletCount = 0;
        float bulletFireRateSecond = 1.0f;
        float bulletFireTimer = bulletFireRateSecond;
        const sf::Color bulletColor = sf::Color{ 0, 255, 0, 255 };
        for (int i = 0; i < bulletCount; i++)
        {
            sf::Vector2f enemyInitPosition = sf::Vector2f{ (float)(screenWidth - 100) , (float)(rand() % screenHeight) };
            bullets[i] = Bullet{ player.getPosition(), sf::Vector2f{1.0f, 0.0f}, 3.0f, bulletColor,  10.0f };
        }

        sf::Clock deltaClock;
        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            float dt = deltaClock.restart().asSeconds();

            // Logic Update

            // Fire bullet
            bulletFireTimer -= dt;
            if (bulletFireTimer < 0.0f)
            {
                bulletFireTimer = bulletFireRateSecond;
                bullets[currentBulletCount] = Bullet{ player.getPosition(), sf::Vector2f{1.0f, 0.0f}, 3.0f, bulletColor,  500.0f };
                currentBulletCount++;
            }

            player.Update(dt);
            for (int i = 0; i < enemyCount; i++)
            {
                enemies[i].Update(dt);
            }
            for (int i = 0; i < currentBulletCount; i++)
            {
                bullets[i].Update(dt);
            }

            // Draw Objects
            window.clear();
            {
                player.Draw(window);

                for (int i = 0; i < enemyCount; i++)
                {
                    enemies[i].Draw(window);
                }
                for (int i = 0; i < bulletCount; i++)
                {
                    bullets[i].Draw(window);
                }

            }
            window.display();
        }

        delete[] enemies;
        delete[] bullets;
    }

    return 0;
}

//--- Practice

// 
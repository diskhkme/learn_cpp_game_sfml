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
#include "Weapon.h"

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

        // Weapon (Bullet 생성)
        const int maxBulletCount = 50;
        Bullet* bullets = new Bullet[maxBulletCount];
        Weapon weapon = Weapon{ bullets, player, 1.0f, maxBulletCount, enemies, enemyCount };

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
            weapon.SpawnBullet(dt);

            player.Update(dt);
            for (int i = 0; i < enemyCount; i++)
            {
                enemies[i].Update(dt);
            }
            for (int i = 0; i < weapon.GetCurrentBulletCount(); i++)
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
                for (int i = 0; i < weapon.GetCurrentBulletCount(); i++)
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
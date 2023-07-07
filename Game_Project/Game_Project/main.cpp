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
#include "Weapon.h"
#include "EnemyManager.h"

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
        Player player = Player{ sf::Vector2f{screenWidth/2.0f, screenHeight/2.0f}, 20.0f, sf::Color{238,108,77,255}, 200.0f };

        // Enemies
        const int maxEnemyCount = 50;
        Enemy* enemies = new Enemy[maxEnemyCount];
        EnemyManager enemyManager = EnemyManager{ &player, enemies, maxEnemyCount, 1.5f, screenWidth, screenHeight };

        // Weapon (Bullet 생성)
        const int maxBullet = 50;
        Bullet* bullets = new Bullet[maxBullet];
        Weapon weapon = Weapon{ bullets, maxBullet, player, 1.0f, enemies, maxEnemyCount };

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
            player.Update(dt);
            enemyManager.Update(dt);
            weapon.Update(dt);

            // Draw Objects
            window.clear();
            {
                player.Draw(window);

                enemyManager.Draw(window);
                
                weapon.Draw(window);

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
#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif


#include <SFML/Graphics.hpp>
#include <vector>
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
        std::vector<Enemy*> enemies;
        enemies.clear();
        const sf::Color enemyColor = sf::Color{ 200, 150, 255, 255 };

        for (int i = 0; i < 10; i++)
        {
            sf::Vector2f enemyInitPosition = sf::Vector2f{ (float)(screenWidth - 100) , (float)(rand() % screenHeight) };
            enemies.emplace_back(new Enemy{ enemyInitPosition , 10.0f, enemyColor, 100.0f, &player });
        }

        // Bullets
        std::vector<Bullet*> bullets;
        bullets.clear();
        const sf::Color bulletColor = sf::Color{ 0, 255, 0, 255 };
        float bulletFirePeriod = 1.0f;
        float bulletFireTimer = bulletFirePeriod;

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
                bulletFireTimer = bulletFirePeriod;
                bullets.emplace_back(new Bullet{ player.getPosition(), sf::Vector2f{1.0f, 0.0f}, 3.0f, bulletColor,  500.0f });
            }

            player.Update(dt);
            for (int i = 0; i < enemies.size(); i++)
            {
                enemies[i]->Update(dt);
            }
            for (int i = 0; i < bullets.size(); i++)
            {
                bullets[i]->Update(dt);
            }

            // Draw Objects
            window.clear();
            {
                player.Draw(window);

                for (int i = 0; i < enemies.size(); i++)
                {
                    enemies[i]->Draw(window);
                }
                for (int i = 0; i < bullets.size(); i++)
                {
                    bullets[i]->Draw(window);
                }

            }
            window.display();
        }

        // Delete
        for (int i = 0; i < enemies.size(); i++)
        {
            delete enemies[i];
        }
        for (int i = 0; i < bullets.size(); i++)
        {
            delete bullets[i];
        }

    }

    return 0;
}

//--- Practice

// 1. Enemy의 복사 생성자를 구현하고, 활용해 보세요.
// 2. Enemy는 Player의 포인터를 가지고 있지만, 소멸자를 구현하지 않았습니다. 괜찮은 걸까요?
// 3. Enemy 클래스를 사용함으로써 개별 객체가 다른 데이터를 가지는 경우를 처리하기가 훨씬 쉬워졌습니다.
//    Enemy를 생성할 때 무작위 색상 또는 크기 또는 속도를 갖고록 수정해 보세요.
//    클래스가 없을 때 이러한 작업을 하려면 코드가 얼마나 복잡해졌을 지 생각해 보세요.
// 4. Enemy가 Player의 위치를 참조하기 위해서 내부적으로 Player의 포인터를 가지도록 했습니다.
//    이를 참조자로 대신하려고 하면 현재 상태에서 어떤 문제가 생길까요?
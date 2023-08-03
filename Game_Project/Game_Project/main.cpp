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

void UpdateEnemiesPosition(float enemySpeed, sf::Vector2f* enemyPositions, int enemyCount, sf::Vector2f playerPosition)
{
    for (int i = 0; i < enemyCount; i++)
    {
        float enemyToPlayerX = playerPosition.x - enemyPositions[i].x;
        float enemyToPlayerY = playerPosition.y - enemyPositions[i].y;

        float length = sqrt(enemyToPlayerX * enemyToPlayerX + enemyToPlayerY * enemyToPlayerY);

        enemyToPlayerX /= length;
        enemyToPlayerY /= length;

        enemyPositions[i].x += enemyToPlayerX * enemySpeed;
        enemyPositions[i].y += enemyToPlayerY * enemySpeed;
    }

}

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
        Player player = Player{ sf::Vector2f{10.0f, 10.0f}, 20.0f, sf::Color{238,108,77,255}, 2.0f };

        // Enemies
        const int enemyCount = 10;
        float enemySpeed = 1.0f;
        sf::Vector2f* enemyPositions = new sf::Vector2f[enemyCount];
        const float enemySize = 10.0f;
        const sf::Color enemyColor = sf::Color{ 200, 150, 255, 255 };
        sf::CircleShape enemies[enemyCount];
        for (int i = 0; i < enemyCount; i++)
        {
            enemyPositions[i].x = screenWidth - 100;
            enemyPositions[i].y = rand() % screenHeight;

            enemies[i] = sf::CircleShape{ enemySize };
            enemies[i].setFillColor(enemyColor);
            enemies[i].setOutlineColor(sf::Color::Red);
            enemies[i].setOutlineThickness(1.0f);
        }

        while (window.isOpen())
        {
            sf::Event event;
            while (window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    window.close();
            }

            // Logic Update
            player.Update();

            UpdateEnemiesPosition(enemySpeed, enemyPositions, enemyCount, player.getPosition());
            for (int i = 0; i < enemyCount; i++)
            {
                enemies[i].setPosition(enemyPositions[i]);
            }

            // Draw Objects
            window.clear();
            {
                player.Draw(window);

                for (int i = 0; i < enemyCount; i++)
                {
                    window.draw(enemies[i]);
                }

            }
            window.display();
        }

        delete[] enemyPositions;
    }

    return 0;
}

//--- Practice

// 1. 강의 자료를 참고하여 Player 클래스를 Player.h/Player.cpp 에 나누어 구현해 보세요.
// 2. Enemy (Enemy들이 아닌 Enemy 한 객체)도 클래스화하여 구현하는 것을 시도해 보세요.
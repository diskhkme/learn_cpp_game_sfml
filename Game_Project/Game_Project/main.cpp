#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif


#include <SFML/Graphics.hpp>

void UpdatePlayerPosition(sf::Vector2f& playerPosition)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        playerPosition.x -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        playerPosition.x += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        playerPosition.y -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        playerPosition.y += 1.0f;
    }
}

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
        sf::Vector2f playerPosition = sf::Vector2f{ 10.0f, 10.0f };
        const float playerSize = 20.0f;
        const sf::Color playerColor = sf::Color{ 238, 108, 77, 255 };
        sf::RectangleShape player = sf::RectangleShape{ sf::Vector2f{playerSize, playerSize} };
        player.setFillColor(playerColor);

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
            UpdatePlayerPosition(playerPosition);

            player.setPosition(playerPosition);

            UpdateEnemiesPosition(enemySpeed, enemyPositions, enemyCount, playerPosition);
            for (int i = 0; i < enemyCount; i++)
            {
                enemies[i].setPosition(enemyPositions[i]);
            }

            // Draw Objects
            window.clear();
            {
                window.draw(player);

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

// 1. 

#define _CRTDBG_MAP_ALLOC
#include <cstdlib>
#include <crtdbg.h>

#ifdef _DEBUG
#define DBG_NEW new ( _NORMAL_BLOCK , __FILE__ , __LINE__ )
#else
#define DBG_NEW new
#endif


#include <SFML/Graphics.hpp>

void UpdatePlayerPosition(float& playerPositionX, float& playerPositionY)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        playerPositionX -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        playerPositionX += 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        playerPositionY -= 1.0f;
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        playerPositionY += 1.0f;
    }
}

void UpdateEnemiesPosition(float enemySpeed, float* enemyPositionX, float* enemyPositionY, int enemyCount, float playerPositionX, float playerPositionY)
{
    for (int i = 0; i < enemyCount; i++)
    {
        float enemyToPlayerX = playerPositionX - enemyPositionX[i];
        float enemyToPlayerY = playerPositionY - enemyPositionY[i];

        float length = sqrt(enemyToPlayerX * enemyToPlayerX + enemyToPlayerY * enemyToPlayerY);

        enemyToPlayerX /= length;
        enemyToPlayerY /= length;

        enemyPositionX[i] += enemyToPlayerX * enemySpeed;
        enemyPositionY[i] += enemyToPlayerY * enemySpeed;
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
        float playerPositionX = 10.0f;
        float playerPositionY = 10.0f;
        const float playerSize = 20.0f;
        const sf::Color playerColor = sf::Color{ 238, 108, 77, 255 };
        sf::RectangleShape player = sf::RectangleShape{ sf::Vector2f{playerSize, playerSize} };
        player.setFillColor(playerColor);

        // Enemies
        const int enemyCount = 10;
        float enemySpeed = 1.0f;
        float* enemyPositionX = new float[enemyCount]; // DBG_NEW 사용 고려
        float* enemyPositionY = new float[enemyCount];
        const float enemySize = 10.0f;
        const sf::Color enemyColor = sf::Color{ 200, 150, 255, 255 };
        sf::CircleShape enemies[enemyCount];
        for (int i = 0; i < enemyCount; i++)
        {
            enemyPositionX[i] = screenWidth - 100;
            enemyPositionY[i] = rand() % screenHeight;

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
            UpdatePlayerPosition(playerPositionX, playerPositionY);
            player.setPosition(sf::Vector2f{ playerPositionX, playerPositionY });

            UpdateEnemiesPosition(enemySpeed, enemyPositionX, enemyPositionY, enemyCount, playerPositionX, playerPositionY);
            for (int i = 0; i < enemyCount; i++)
            {
                enemies[i].setPosition(sf::Vector2f{ enemyPositionX[i], enemyPositionY[i] });
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

        delete[] enemyPositionX;
        delete[] enemyPositionY;
    }
    
    return 0;
}

//--- Practice

// 1. 각 Update...() 함수 안에서, setPosition() 함수
// 2. enemies 배열도 동적 할당된 배열로 수정해 보세요.

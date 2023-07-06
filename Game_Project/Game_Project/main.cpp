#include <SFML/Graphics.hpp>

void Update(float& playerPositionX, float& playerPositionY)
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

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "03_Function_Enemies");
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
    float enemyPositionX[enemyCount];
    float enemyPositionY[enemyCount];
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
        Update(playerPositionX, playerPositionY);

        player.setPosition(sf::Vector2f{ playerPositionX, playerPositionY });

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

    return 0;
}

//--- Practice

// 1. 적들의 숫자를 늘려 보세요.
// 2. 적들을 왼쪽이 아니라 아래쪽 부분에 랜덤하게 생성되도록 바꿔 보세요.
// 3. 적들이 생성된 후 왼쪽으로 움직이도록 코드를 작성해 보세요.
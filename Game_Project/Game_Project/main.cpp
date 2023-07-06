#include <SFML/Graphics.hpp>

float UpdateLeft(float currentPlayerPositionX)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        currentPlayerPositionX -= 1.0f;
    }
    else
    {
        return currentPlayerPositionX;
    }
}

float UpdateRight(float currentPlayerPositionX)
{
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        currentPlayerPositionX += 1.0f;
    }
    else
    {
        return currentPlayerPositionX;
    }
}

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "03_Function");
    window.setFramerateLimit(60);

    float playerPositionX = 10.0f;
    float playerPositionY = 10.0f;
    const float playerSize = 20.0f;
    const sf::Color playerColor = sf::Color{ 238, 108, 77, 255 };
    sf::RectangleShape player = sf::RectangleShape{ sf::Vector2f{playerSize, playerSize} };
    player.setFillColor(playerColor);

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // Logic Update
        playerPositionX = UpdateLeft(playerPositionX);
        playerPositionX = UpdateRight(playerPositionX);

        player.setPosition(sf::Vector2f{ playerPositionX, playerPositionY });

        // Draw Objects
        window.clear();
        {
            window.draw(player);
        }
        window.display();
    }

    return 0;
}

//--- Practice

// 1. W,S 키로 플레이어가 위아래로도 움직일 수 있도록 수정해 보세요.
// 2. 플레이어의 속도가 너무 느린 것 같습니다. 속도를 더 빠르게 바꾸어 보세요. 효율적으로 하기 위해 playerSpeed 변수를 선언해서 구현해 보세요.
// 3. W,S키를 사용하게 되어서 함수가 4개나 되었습니다. 포인터 또는 참조자를 사용해서 모든 움직임을 하나의 함수에서 처리할 수 있도록 시도해 보세요.
// 4. 마우스 입력은 어떻게 처리하는걸까요? 스스로 한 번 찾아보세요!
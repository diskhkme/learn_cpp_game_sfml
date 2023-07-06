#include <SFML/Graphics.hpp>

int main()
{
    int screenWidth = 800;
    int screenHeight = 450;

    sf::RenderWindow window(sf::VideoMode(screenWidth, screenHeight), "01_Variable");

    float rectPositionX = 10;
    float rectPositionY = 50;
    float rectWidth = 20.0f;
    float rectHeight = 10.0f;

    sf::RectangleShape rect(sf::Vector2f{ rectWidth, rectHeight });
    rect.setFillColor(sf::Color{ 238,108,77,255 });

    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        rectPositionX += 0.05f;
        rect.setPosition(rectPositionX, rectPositionY);

        window.clear();
        window.draw(rect);
        window.display();
    }

    return 0;
}

//--- Practice

// 1. 사각형의 이동 속도를 더 증가시켜보세요.
// 2. 사각형의 이동 방향을 바꿔 보세요. 예를들어 오른쪽 아래로 이동하도록 해 보세요.
// 3. 사각형이 화면 끝까지 가면 사라져버립니다. 이럴 경우 화면 왼쪽에서 다시 나타나도록 코드를 수정해 보세요.
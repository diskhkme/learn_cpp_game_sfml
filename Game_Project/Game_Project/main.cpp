#include <SFML/Graphics.hpp>
#include <iostream>

int main()
{
    // 화면을 그릴 윈도우 생성
    sf::RenderWindow window(sf::VideoMode(1024, 768), "SFML works!");

    // 글을 표시하고 싶을 경우 폰트 로딩 필요
    sf::Font font;
    if (!font.loadFromFile("../resources/font/arial.ttf"))
    {
        std::cout << "Font Loading Error!" << std::endl;
    }

    // 화면에 그릴 원 객체 생성
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    // 화면에 그릴 텍스트 객체 생성
    sf::Text text;
    text.setFont(font);
    text.setString("Hello SFML!");
    text.setCharacterSize(24);
    text.setFillColor(sf::Color::White);

    // 윈도우가 열려 있을 동안 반복
    while (window.isOpen())
    {
        // 종료 조건
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        //--- 화면을 그리는 세 단계

        // 1) 이미 그려져 있는 모든 것을 지운다.
        window.clear(); 

        // 2) 그리고 싶은 것들을 draw 함수를 사용해 그린다.
        window.draw(shape);
        window.draw(text);

        // 3) 화면에 표시한다.
        window.display();
    }

    return 0;
}

//--- Practice

// 1. 화면의 크기를 더 크게, 또는 더 작게 만들어 보세요.
// 2. 원을 화면의 다른 위치에, 다른 크기로 만들어 보세요.
// 3. 원 개신 사각형을 화면에 그려 보세요. (https://www.sfml-dev.org/documentation/2.6.0/classsf_1_1RectangleShape.php)
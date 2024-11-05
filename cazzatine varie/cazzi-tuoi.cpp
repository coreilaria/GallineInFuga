#include <SFML/Graphics.hpp>

int main()
{
    sf::RenderWindow window(sf::VideoMode(2000, 2000), "SFML works!");
    sf::CircleShape shape1(100.f);
    sf::CircleShape shape2(100.f);
    sf::CircleShape shape3(100.f);
    sf::CircleShape shape4(100.f);
    
    sf::RectangleShape rectangle1(sf::Vector2f(2000.f, 2000.f));
    sf::RectangleShape rectangle(sf::Vector2f(200.f, 550.f));
    rectangle1.setFillColor(sf::Color::White);

    rectangle.setFillColor(sf::Color::Cyan);
    shape1.setFillColor(sf::Color::Cyan);
    shape2.setFillColor(sf::Color::Cyan);
    shape3.setFillColor(sf::Color::Cyan);
    shape4.setFillColor(sf::Color::Red);

    rectangle1.setPosition(0.f,0.f);
    shape1.setPosition(400.f,600.f);
    shape2.setPosition(600.f,600.f);
    rectangle.setPosition(500.f,150.f);
    shape3.setPosition(500.f,50.f);
    shape4.setPosition(-100.f,-100.f);
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        window.clear();
        window.draw(rectangle1);
        window.draw(shape1);
        window.draw(shape2);
        window.draw(rectangle);
        window.draw(shape3);
        window.draw(shape4);
        window.display();
    }

    return 0;


    
}



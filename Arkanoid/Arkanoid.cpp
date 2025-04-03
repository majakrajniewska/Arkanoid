#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Bar.h"

int main()
{
    srand(time(0));
    unsigned int SCREEN_HEIGHT = 900;
    unsigned int SCREEN_WIDTH = 900;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "ARKANOID");
    
    Ball ball(30.f, SCREEN_WIDTH, SCREEN_HEIGHT);
    Bar bar(150.f, 30.f, 10.f, SCREEN_WIDTH, SCREEN_HEIGHT);

    window->setFramerateLimit(60);

    while (window->isOpen())
    {
        while (const std::optional event = window->pollEvent())
        {
            //Close window
            if (event->is<sf::Event::Closed>())
                window->close();
            //Keys pressed
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                //Escape
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window->close();
                //A
                else if (keyPressed->scancode == sf::Keyboard::Scancode::A)
                    bar.update(*window, -1);
                //D
                else if (keyPressed->scancode == sf::Keyboard::Scancode::D)
                    bar.update(*window, 1);
            }
        }
        ball.update(*window, bar);

        window->clear();
        ball.draw(*window);
        bar.draw(*window);
        window->display();
    }
}
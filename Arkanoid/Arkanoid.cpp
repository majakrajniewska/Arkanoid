#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Bar.h"
#include "Block.h"

int main()
{
    srand(time(0));
    unsigned int SCREEN_HEIGHT = 900;
    unsigned int SCREEN_WIDTH = 900;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "ARKANOID");
    
    Ball ball(30.f, SCREEN_WIDTH, SCREEN_HEIGHT);
    Bar bar(150.f, 30.f, 10.f, SCREEN_WIDTH, SCREEN_HEIGHT);

    //Map
    std::vector<std::vector<int>> map = {
        {1, 2, 0, 3, 1, 1, 3, 0, 2, 1},
        {0, 3, 2, 0, 1, 1, 0, 2, 3, 0},
        {2, 1, 1, 0, 3, 3, 0, 1, 1, 2},
        {1, 0, 3, 2, 0, 0, 2, 3, 0, 1}
    };

    std::vector<Block*> blocks;

    //generating map
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] != 0) {
                blocks.push_back(new Block(80, 80, j * 85, i * 85, map[i][j]));
            }
        }
    }

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
        ball.update(*window, bar, blocks);

        window->clear();
        ball.draw(*window);
        bar.draw(*window);
        for(Block *b : blocks) {
            b->draw(*window);
        }
        window->display();
    }
}
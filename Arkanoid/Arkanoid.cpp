#include <SFML/Graphics.hpp>
#include "Ball.h"
#include "Bumper.h"
#include "Block.h"
#include "GameHandler.h"

int main()
{
    srand(time(0));
    unsigned int SCREEN_HEIGHT = 900;
    unsigned int SCREEN_WIDTH = 900;
    sf::RenderWindow window = sf::RenderWindow(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "ARKANOID");
    GameHandler gameHandler(3);
    
    Ball ball(25.f, SCREEN_WIDTH, SCREEN_HEIGHT);
    Bumper bumper(170.f, 30.f, 8.f, SCREEN_WIDTH, SCREEN_HEIGHT);

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

    window.setFramerateLimit(60);

    while (window.isOpen())
    {
        // Real-time movement (no delay when holding keys)
        //A pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A)) {
            bumper.update(window, -1.f);
        }
        //D pressed
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D)) {
            bumper.update(window, 1.f);
        }
        while (const std::optional event = window.pollEvent())
        {
            //Close window
            if (event->is<sf::Event::Closed>())
                window.close();
            //Keys pressed
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                //Escape
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window.close();
            }
        }
        ball.update(window, gameHandler, bumper, blocks);

        window.clear();
        ball.draw(window);
        bumper.draw(window);
        bumper.draw(window);
        for(Block *b : blocks) {
            b->draw(window);
        }
        window.display();
    }
}
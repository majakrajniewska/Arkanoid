#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "GamePlayingState.h"

int main() {
    unsigned int SCREEN_WIDTH = 900;
    unsigned int SCREEN_HEIGHT = 900;

    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "ARKANOID");
    window.setFramerateLimit(60);

    StateManager manager;
    manager.push(std::make_unique<GamePlayingState>(window, SCREEN_WIDTH, SCREEN_HEIGHT));


    sf::Clock clock;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            manager.handleEvent(*event); // Dereference the optional
        }

        float dt = clock.restart().asSeconds();
        manager.update(dt);

        if (auto* game = dynamic_cast<GamePlayingState*>(manager.top())) {
            if (game->shouldExit())
                window.close(); // Later you can switch to GameOverState or Menu
        }

        manager.render(window);
    }
}

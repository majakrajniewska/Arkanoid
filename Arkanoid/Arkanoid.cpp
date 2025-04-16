#include <SFML/Graphics.hpp>
#include "StateManager.h"
#include "GamePlayingState.h"
#include "MenuState.h"

int main() {
    unsigned int SCREEN_WIDTH = 900;
    unsigned int SCREEN_HEIGHT = 900;

    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "ARKANOID");
    window.setFramerateLimit(60);

    sf::Font font;
    font.openFromFile("assets/fonts/Junicode.ttf");

    sf::Texture buttonTex;
    // buttonTex.loadFromFile("path/to/button-image.png"); // optional

    MenuState menu(window, font);
    //MENU LOOP

    while (window.isOpen() && !menu.shouldExit() && !menu.shouldStartGame()) {
        while (auto event = window.pollEvent()) {
            menu.handleEvent(*event);
        }
        menu.render(window);
    }

    if (menu.shouldExit()) {
        window.close();
        return 0;
    }

    StateManager manager;
    manager.push(std::make_unique<GamePlayingState>(window, SCREEN_WIDTH, SCREEN_HEIGHT, menu.getSelectedDifficulty()));


    sf::Clock clock;

    //GAME LOOP
    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            manager.handleEvent(*event);
        }

        float dt = clock.restart().asSeconds();
        manager.update(dt);

        if (auto* game = dynamic_cast<GamePlayingState*>(manager.top())) {
            if (game->shouldExit())
                window.close(); // Later switch to GameOverState or Menu
        }

        manager.render(window);
    }
}

#include <SFML/Graphics.hpp>
#include <iostream>
#include "StateManager.h"
#include "GamePlayingState.h"
#include "MenuState.h"

void openMenu(sf::RenderWindow& window, MenuState& menu) {
    menu.reset();
    std::cout << "ENTER MENU...";
    while (window.isOpen() && !menu.shouldExit() && !menu.shouldStartGame()) {
        while (auto event = window.pollEvent()) {
            menu.handleEvent(*event);
        }
        menu.render(window);
    }
}

void runGame(StateManager& manager, sf::RenderWindow& window, sf::Font& font, Difficulty difficulty, BallSpeed ballSpeed) {
    manager.push(std::make_unique<GamePlayingState>(window, 900, 900, difficulty, ballSpeed));
    sf::Clock clock;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            manager.handleEvent(*event);
        }

        float dt = clock.restart().asSeconds();
        manager.update(dt);

        if (auto* game = dynamic_cast<GamePlayingState*>(manager.top())) {
            if (game->shouldExit()) {
                break;
            }
        }

        manager.render(window);
    }
    manager.pop();
}

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
    StateManager manager;

    while (window.isOpen()) {
        openMenu(window, menu);
        if (menu.shouldExit()) break;
        runGame(manager, window, font, menu.getSelectedDifficulty(), menu.getSelectedBallSpeed());
    }

    return 0;
}


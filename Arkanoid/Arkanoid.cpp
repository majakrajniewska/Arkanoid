#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "StateManager.h"
#include "GamePlayingState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameOverState.h"

const unsigned int GAME_SIZE = 900;

void runGame(StateManager& manager, sf::RenderWindow& window, sf::Font& font, 
    Difficulty difficulty, BallSpeed ballSpeed, bool& restart) {
    manager.push(std::make_unique<GamePlayingState>(window, 900, 900, difficulty, ballSpeed, font));
    sf::Clock clock;

    bool closeWindow = false;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            manager.handleEvent(*event);
        }

        float dt = clock.restart().asSeconds();
        manager.update(dt);

        if (manager.top()->handleManager(manager, restart, closeWindow)) {
            if (closeWindow) { 
                window.close(); 
                return;
            }
            break;
        }

        manager.render(window);
    }
}

int main() {
    std::srand(static_cast<unsigned>(std::time(nullptr)));
    unsigned int SCREEN_WIDTH = 900;
    unsigned int SCREEN_HEIGHT = 900;

    sf::RenderWindow window(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "ARKANOID");
    window.setFramerateLimit(60);

    sf::Font font;
    font.openFromFile("assets/fonts/Junicode.ttf");

    sf::Texture buttonTex;
    //buttonTex.loadFromFile("path/to/button-image.png"); // optional

    StateManager manager(GAME_SIZE);
    bool restart = false;

    manager.push(std::make_unique<MenuState>(window, font));

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
            manager.handleEvent(*event);
        }

        manager.render(window);

        if (auto* menu = dynamic_cast<MenuState*>(manager.top())) {
            if (menu->shouldExit()) {
                manager.pop();  // pop menu
                break;
            }
            if (menu->shouldStartGame() || restart) {
                Difficulty diff = menu->getSelectedDifficulty();
                BallSpeed speed = menu->getSelectedBallSpeed();
                menu->reset();  // reset selection for next time
                restart = false;
                runGame(manager, window, font, diff, speed, restart);
            }
        }
    }

    return 0;
}


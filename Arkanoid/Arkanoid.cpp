#include <SFML/Graphics.hpp>
#include <iostream>
#include <memory>
#include "StateManager.h"
#include "GamePlayingState.h"
#include "MenuState.h"
#include "PauseState.h"
#include "GameOverState.h"

void runGame(StateManager& manager, sf::RenderWindow& window, sf::Font& font, 
    Difficulty difficulty, BallSpeed ballSpeed, bool& restart) {
    manager.push(std::make_unique<GamePlayingState>(window, 900, 900, difficulty, ballSpeed, font));
    sf::Clock clock;

    while (window.isOpen()) {
        while (auto event = window.pollEvent()) {
            manager.handleEvent(*event);
        }

        float dt = clock.restart().asSeconds();
        manager.update(dt);

        if (auto* game = dynamic_cast<GamePlayingState*>(manager.top())) {
            if (game->shouldPause()) {
                game->reset();
                manager.push(std::make_unique<PauseState>(window, font));
                continue; // wait for pause state to handle events
            }
            if (game->shouldExit()) {
                manager.pop(); // pop GamePlayingState
                break;
            }
            if (game->isOver()) {
                manager.push(std::make_unique<GameOverState>(window, font, game->getTime(), 
                    game->getGameHandler().getPoints(), !game->getGameHandler().checkLose()));
                continue; // wait for gameOver state to handle events
            }
        }

        if (auto* pause = dynamic_cast<PauseState*>(manager.top())) {
            if (pause->shouldStartGame()) {
                manager.pop(); // resume: pop pause state
            }
            else if (pause->shouldGoBackToMenu()) {
                manager.pop(); // pop PauseState
                manager.pop(); // pop GamePlayingState
                break;
            }
            else if (pause->shouldExit()) {
                manager.pop(); // pop PauseState
                manager.pop(); // pop GamePlayingState
                manager.pop(); // pop menu
                window.close();
                break;
            }
        }

        //ADD GAME OVER STATE HANDLING
        if (auto* over = dynamic_cast<GameOverState*>(manager.top())) {
            if (over->shouldRestartGame()) {
                manager.pop(); // pop GameOverState
                manager.pop(); // pop GamePlayingState
                restart = true;
                break;
            }
            else if (over->shouldGoBackToMenu()) {
                manager.pop(); // pop GameOverState
                manager.pop(); // pop GamePlayingState
                break;
            }
            else if (over->shouldExit()) {
                manager.pop(); // pop GameOverState
                manager.pop(); // pop GamePlayingState
                manager.pop(); // pop menu
                window.close();
                break;
            }
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

    StateManager manager;
    bool restart = false;

    //add menu to the manager - stack
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


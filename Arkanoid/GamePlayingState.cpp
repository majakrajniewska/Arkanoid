#include "GamePlayingState.h"

GamePlayingState::GamePlayingState(sf::RenderWindow& win, unsigned int screenW, unsigned int screenH)
    : window(win), windowWidth(screenW), windowHeight(screenH),
    ball(25.f, screenW, screenH),
    bumper(170.f, 30.f, 8.f, screenW, screenH),
    gameHandler(3)
{
    std::vector<std::vector<int>> map = {
        {1, 2, 0, 3, 1, 1, 3, 0, 2, 1},
        {0, 3, 2, 0, 1, 1, 0, 2, 3, 0},
        {2, 1, 1, 0, 3, 3, 0, 1, 1, 2},
        {1, 0, 3, 2, 0, 0, 2, 3, 0, 1}
    };

    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] != 0) {
                blocks.push_back(std::make_unique<Block>(80, 80, j * 85, i * 85, map[i][j]));
            }
        }
    }
}

void GamePlayingState::handleEvent(sf::Event& event) {
    if (event.is<sf::Event::Closed>())
        exitRequested = true;
    else if (event.is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))
        exitRequested = true;
}

void GamePlayingState::update(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::A))
        bumper.update(windowWidth, -1.f);
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::D))
        bumper.update(windowWidth, 1.f);

    ball.update(window, gameHandler, bumper, blocks);

    if (gameHandler.checkLose() || blocks.empty()) {
        exitRequested = true;
    }
}

void GamePlayingState::render(sf::RenderWindow& window) {
    window.clear();
    ball.draw(window);
    bumper.draw(window);
    for (const auto& b : blocks)
        b->draw(window);
    window.display();
}

bool GamePlayingState::shouldExit() const {
    return exitRequested;
}

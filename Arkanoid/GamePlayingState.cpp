#include "GamePlayingState.h"

GamePlayingState::GamePlayingState(sf::RenderWindow& win, unsigned int screenW, unsigned int screenH, Difficulty difficulty, BallSpeed speed)
    : window(win), windowWidth(screenW), windowHeight(screenH),
    ball(25.f, screenW, screenH, speed),
    bumper(170.f, 30.f, 8.f, screenW, screenH),
    gameHandler(3), difficulty(difficulty)
{
    std::vector<std::vector<int>> mapSimple = {
        {1, 0, 2, 0, 1, 0, 2, 0},
        {0, 1, 0, 2, 0, 1, 0, 2},
        {2, 0, 1, 0, 2, 0, 1, 0}
    };

    std::vector<std::vector<int>> mapNormal = {
        {1, 2, 0, 3, 1, 1, 3, 0, 2, 1},
        {0, 3, 2, 0, 1, 1, 0, 2, 3, 0},
        {2, 1, 1, 0, 3, 3, 0, 1, 1, 2},
        {1, 0, 3, 2, 0, 0, 2, 3, 0, 1}
    };

    std::vector<std::vector<int>> mapHard = {
        {2, 3, 0, 3, 2, 0, 3, 2, 1, 0, 2, 1},
        {3, 0, 2, 0, 3, 2, 0, 3, 2, 1, 3, 0},
        {0, 3, 2, 0, 3, 0, 2, 1, 0, 3, 2, 1},
        {3, 1, 0, 2, 1, 3, 0, 2, 3, 0, 1, 0},
        {1, 2, 3, 0, 2, 3, 0, 3, 2, 0, 1, 2},
    };
    switch (difficulty) {
    case Difficulty::Easy: generateMap(mapSimple); break;
    case Difficulty::Medium: generateMap(mapNormal); break;
    case Difficulty::Hard: generateMap(mapHard); break;
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

void GamePlayingState::generateMap(std::vector<std::vector<int>> map)
{
    float blockSize = windowWidth / map[0].size();
    for (int i = 0; i < map.size(); i++) {
        for (int j = 0; j < map[0].size(); j++) {
            if (map[i][j] != 0) {
                blocks.push_back(std::make_unique<Block>(blockSize, blockSize,
                    j * blockSize, i * blockSize, map[i][j]));
            }
        }
    }
}

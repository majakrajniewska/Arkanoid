#pragma once

#include "GameState.h"
#include "Ball.h"
#include "Bumper.h"
#include "Block.h"
#include "GameHandler.h"
#include <vector>
#include <memory>

class GamePlayingState : public GameState {
public:
    GamePlayingState(sf::RenderWindow& win, unsigned int screenW, unsigned int screenH);

    void handleEvent(sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    bool shouldExit() const;

private:
    sf::RenderWindow& window;
    unsigned int windowWidth, windowHeight;

    Ball ball;
    Bumper bumper;
    GameHandler gameHandler;
    std::vector<std::unique_ptr<Block>> blocks;
    bool exitRequested = false;
};
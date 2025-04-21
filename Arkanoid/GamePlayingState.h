#pragma once

#include "GameState.h"
#include "Ball.h"
#include "Bumper.h"
#include "Block.h"
#include "GameHandler.h"
#include <vector>
#include <memory>
#include "Difficulty.h"
#include "BallSpeed.h"
#include "HUD.h"

class GamePlayingState : public GameState {
public:
    GamePlayingState(sf::RenderWindow& win, unsigned int screenW, unsigned int screenH, Difficulty difficulty, BallSpeed speed, sf::Font& font);

    void handleEvent(sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    bool shouldExit() const;
    bool shouldPause() const;
    void reset();
    float getTime() const;
    GameHandler getGameHandler() const;
    bool isOver() const;

private:
    sf::RenderWindow& window;
    unsigned int windowWidth, windowHeight;

    Ball ball;
    Bumper bumper;
    GameHandler gameHandler;
    std::vector<std::unique_ptr<Block>> blocks;
    bool exitRequested = false;
    bool pauseRequested = false;
    Difficulty difficulty;
    float pointsCoefficient = 1;
    HUD hud;
    float timePassed = 0.f;
    bool over = false;

    void generateMap(std::vector<std::vector<int>> map);
};
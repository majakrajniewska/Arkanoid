#pragma once

#include "GameState.h"
#include "Button.h"
#include <vector>
#include <memory>
#include "Difficulty.h"
#include "BallSpeed.h"

class MenuState : public GameState {
public:
    MenuState(sf::RenderWindow& window, sf::Font& font, const sf::Texture* buttonTexture = nullptr);

    void handleEvent(sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    sf::RenderWindow* getWindow() override { return &window; }

    bool shouldStartGame() const;
    bool shouldExit() const;
    Difficulty getSelectedDifficulty() const;
    BallSpeed getSelectedBallSpeed() const;
    void reset();

private:
    sf::RenderWindow& window;
    sf::Font& font;
    const sf::Texture* buttonTexture;

    std::vector<std::unique_ptr<Button>> buttons;
    bool startGame = false;
    bool exitRequested = false;

    Difficulty currentDifficulty = Difficulty::Easy;
    BallSpeed currentSpeed = BallSpeed::Slow;

    void updateButtonTexts();
};



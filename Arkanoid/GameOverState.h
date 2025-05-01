#pragma once
#include "GameState.h"
#include "Button.h"
#include "GameHandler.h"

class GameOverState : public GameState {
public:
    GameOverState(sf::RenderWindow& window, sf::Font& font, 
        float time, int points, bool win, const sf::Texture* buttonTexture = nullptr);

    void handleEvent(sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    sf::RenderWindow* getWindow() override { return &window; }

    bool shouldRestartGame() const;
    bool shouldGoBackToMenu() const;
    bool shouldExit() const;
    void reset();

private:
    void setTextPosition(sf::Text& label, float x, float y);
    sf::RenderWindow& window;
    sf::Font& font;
    const sf::Texture* buttonTexture;

    std::vector<std::unique_ptr<Button>> buttons;
    bool restartGame = false;
    bool goBackToMenu = false;
    bool exitRequested = false;

    int points;
    float time;
    bool win;
    sf::Text header;
    sf::Text pointsText;
    sf::Text timeText;

};



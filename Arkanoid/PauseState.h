#pragma once
#include "GameState.h"
#include "Button.h"
#include <SFML/Graphics.hpp>
#include "StateManager.h"

class PauseState : public GameState {
public:
    PauseState(sf::RenderWindow& window, sf::Font& font, const sf::Texture* buttonTexture = nullptr);

    void handleEvent(sf::Event& event) override;
    void update(float dt) override;
    void render(sf::RenderWindow& window) override;
    sf::RenderWindow* getWindow() override { return &window; }
    bool handleManager(StateManager& manager, bool& restart, bool& closeWindow) override;

    bool shouldStartGame() const;
    bool shouldGoBackToMenu() const;
    bool shouldExit() const;
    bool isTransparent() const override { return true; }

private:
    sf::RenderWindow& window;
    sf::Font& font;
    const sf::Texture* buttonTexture;

    std::vector<std::unique_ptr<Button>> buttons;

    bool resumeRequested = false;
    bool menuRequested = false;
    bool exitRequested = false;
};

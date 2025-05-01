#pragma once

#include <SFML/Graphics.hpp>
#include "Button.h" // assuming you already have a Button class

class HUD {
public:
    HUD(sf::Font& font, const sf::Texture* buttonTexture = nullptr);

    void update(float elapsedTime, int currentPoints, int currentLives);
    void draw(sf::RenderWindow& window);

    void handleEvent(const sf::Event& event, const sf::RenderWindow& window);

    bool pausePressed() const { return pauseRequested; }
    void resetPause() { pauseRequested = false; }
    float getHeight() const { return 100.f; } //temporary

private:
    sf::Text timeText;
    sf::Text pointsText;
    sf::Text livesText;
    std::unique_ptr<Button> pauseButton;

    bool pauseRequested = false;
};



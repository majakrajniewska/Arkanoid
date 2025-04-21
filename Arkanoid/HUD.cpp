#include "HUD.h"

HUD::HUD(sf::Font& font, const sf::Texture* buttonTexture) 
    : timeText(font), pointsText(font) {
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition({ 100, 10 });

    pointsText.setCharacterSize(30);
    pointsText.setFillColor(sf::Color::White);
    pointsText.setPosition({ 300, 10 });

    pauseButton = std::make_unique<Button>("Pause", sf::Color(100, 100, 200), font, 300, 60);
    pauseButton->setPosition(500, 10);
}

void HUD::update(float elapsedTime, int currentPoints) {
    int minutes = static_cast<int>(elapsedTime) / 60;
    int seconds = static_cast<int>(elapsedTime) % 60;

    std::ostringstream timeStream;
    timeStream << "Time: " << std::setw(2) << std::setfill('0') << minutes
        << ":" << std::setw(2) << std::setfill('0') << seconds;

    timeText.setString(timeStream.str());

    pointsText.setString("Points: " + std::to_string(currentPoints));
}

void HUD::draw(sf::RenderWindow& window) {
    window.draw(timeText);
    window.draw(pointsText);
    pauseButton->draw(window);
}

void HUD::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.is<sf::Event::MouseButtonPressed>()) {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        if (pauseButton->isHovered(mousePos)) {
            pauseRequested = true;
        }
    }
}

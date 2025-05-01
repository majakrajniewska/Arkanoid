#include "HUD.h"

HUD::HUD(sf::Font& font, const sf::Texture* buttonTexture) 
    : timeText(font), pointsText(font), livesText(font) {
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::White);
    timeText.setPosition({ 50, 10 });

    pointsText.setCharacterSize(30);
    pointsText.setFillColor(sf::Color::White);
    pointsText.setPosition({ 240, 10 });

    livesText.setCharacterSize(30);
    livesText.setFillColor(sf::Color::White);
    livesText.setPosition({ 400, 10 });

    pauseButton = std::make_unique<Button>("Pause", sf::Color(100, 100, 200), font, 300, 60);
    pauseButton->setPosition(550, 10);
}

void HUD::update(float elapsedTime, int currentPoints, int currentLives) {
    int minutes = static_cast<int>(elapsedTime) / 60;
    int seconds = static_cast<int>(elapsedTime) % 60;

    std::ostringstream timeStream;
    timeStream << "Time: " << std::setw(2) << std::setfill('0') << minutes
        << ":" << std::setw(2) << std::setfill('0') << seconds;

    timeText.setString(timeStream.str());

    pointsText.setString("Points: " + std::to_string(currentPoints));

    livesText.setString("Lives: " + std::to_string(currentLives));
}

void HUD::draw(sf::RenderWindow& window) {
    window.draw(timeText);
    window.draw(pointsText);
    window.draw(livesText);
    pauseButton->draw(window);
}

void HUD::handleEvent(const sf::Event& event, const sf::RenderWindow& window) {
    if (event.is<sf::Event::MouseButtonPressed>()) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

        if (pauseButton->isHovered(worldPos)) {
            pauseRequested = true;
        }
    }
}

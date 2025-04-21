#include "MenuState.h"
#include <iostream>

MenuState::MenuState(sf::RenderWindow& window, sf::Font& font, const sf::Texture* buttonTexture)
    : window(window), font(font), buttonTexture(buttonTexture)
{
    auto createButton = [&](const std::string& text) {
        if (buttonTexture)
            return std::make_unique<Button>(text, *buttonTexture, font, 300, 60);
        else
            return std::make_unique<Button>(text, sf::Color(100, 100, 200), font, 300, 60);
        };

    buttons.push_back(createButton("Map: Medium"));
    buttons.push_back(createButton("Ball: Normal"));
    buttons.push_back(createButton("Play"));
    buttons.push_back(createButton("Exit"));

    float startY = 250.f;
    for (size_t i = 0; i < buttons.size(); ++i) {
        buttons[i]->setPosition(window.getSize().x / 2.f - buttons[i]->getWidth() / 2.f, startY + i * 80.f);
    }
}

void MenuState::handleEvent(sf::Event& event) {
    if (event.is<sf::Event::MouseButtonPressed>()) {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        if (buttons[0]->isHovered(mousePos)) { // Difficulty
            currentDifficulty = static_cast<Difficulty>((static_cast<int>(currentDifficulty) + 1) % 3);
        }
        else if (buttons[1]->isHovered(mousePos)) { // Speed
            currentSpeed = static_cast<BallSpeed>((static_cast<int>(currentSpeed) + 1) % 3);
        }
        else if (buttons[2]->isHovered(mousePos)) { // Play
            startGame = true;
        }
        else if (buttons[3]->isHovered(mousePos)) { // Exit
            exitRequested = true;
        }

        updateButtonTexts();
    }
    else if (event.is<sf::Event::Closed>() || 
        (event.is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))) {
        exitRequested = true;
    }
}

void MenuState::update(float) {}

void MenuState::render(sf::RenderWindow& window) {
    window.clear();
    for (const auto& btn : buttons)
        btn->draw(window);
    window.display();
}

bool MenuState::shouldStartGame() const {
    return startGame;
}

bool MenuState::shouldExit() const {
    return exitRequested;
}

Difficulty MenuState::getSelectedDifficulty() const {
    return currentDifficulty;
}

BallSpeed MenuState::getSelectedBallSpeed() const {
    return currentSpeed;
}

void MenuState::reset()
{
    startGame = false;
    exitRequested = false;
}

void MenuState::updateButtonTexts() {
    std::string diffText = "Map: ";
    switch (currentDifficulty) {
    case Difficulty::Easy: diffText += "Easy"; break;
    case Difficulty::Medium: diffText += "Medium"; break;
    case Difficulty::Hard: diffText += "Hard"; break;
    }

    std::string speedText = "Ball: ";
    switch (currentSpeed) {
    case BallSpeed::Slow: speedText += "Slow"; break;
    case BallSpeed::Normal: speedText += "Normal"; break;
    case BallSpeed::Fast: speedText += "Fast"; break;
    }

    buttons[0]->setText(diffText);
    buttons[1]->setText(speedText);

    buttons[0]->centerLabel(buttons[0]->getX(), buttons[0]->getY());
    buttons[1]->centerLabel(buttons[1]->getX(), buttons[1]->getY());
}


#include "PauseState.h"

PauseState::PauseState(sf::RenderWindow& window, sf::Font& font, const sf::Texture* buttonTexture)
	: window(window), font(font), buttonTexture(buttonTexture)
{
    auto createButton = [&](const std::string& text) {
        if (buttonTexture)
            return std::make_unique<Button>(text, *buttonTexture, font, 300, 60);
        else
            return std::make_unique<Button>(text, sf::Color(100, 100, 200), font, 300, 60);
        };

    buttons.push_back(createButton("Resume"));
    buttons.push_back(createButton("Menu"));
    buttons.push_back(createButton("Exit"));

    float startY = 200.f;
    for (size_t i = 0; i < buttons.size(); ++i) {
        buttons[i]->setPosition(window.getSize().x / 2.f - buttons[i]->getWidth() / 2.f, startY + i * 80.f);
    }
}

void PauseState::handleEvent(sf::Event& event)
{
    if (event.is<sf::Event::MouseButtonPressed>()) {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        if (buttons[0]->isHovered(mousePos)) { // Resume
            resumeRequested = true;
        }
        else if (buttons[1]->isHovered(mousePos)) { // Menu
            menuRequested = true;
        }
        else if (buttons[2]->isHovered(mousePos)) { // Exit
            exitRequested = true;
        }
    }
    else if (event.is<sf::Event::Closed>() ||
        (event.is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))) {
        resumeRequested = true;
    }
}

void PauseState::update(float dt)
{
}

void PauseState::render(sf::RenderWindow& window) {
    window.clear();
    for (const auto& btn : buttons)
        btn->draw(window);
    window.display();
}

bool PauseState::shouldStartGame() const
{
    return resumeRequested;
}

bool PauseState::shouldGoBackToMenu() const
{
    return menuRequested;
}

bool PauseState::shouldExit() const
{
    return exitRequested;
}

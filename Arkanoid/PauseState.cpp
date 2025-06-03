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

    sf::Vector2f viewCenter = window.getView().getCenter();
    float startY = viewCenter.y - viewCenter.y / 4.f;
    for (size_t i = 0; i < buttons.size(); ++i) {
        buttons[i]->setPosition(viewCenter.x - buttons[i]->getWidth() / 2.f, startY + i * 80.f);
    }
}

void PauseState::handleEvent(sf::Event& event)
{
    if (event.is<sf::Event::MouseButtonPressed>()) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

        if (buttons[0]->isHovered(worldPos)) { // Resume
            resumeRequested = true;
        }
        else if (buttons[1]->isHovered(worldPos)) { // Menu
            menuRequested = true;
        }
        else if (buttons[2]->isHovered(worldPos)) { // Exit
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

bool PauseState::handleManager(StateManager& manager, bool& restart, bool& closeWindow)
{
    if (shouldStartGame()) {
        manager.pop(); // resume: pop pause state
        return false;
    }
    else if (shouldGoBackToMenu()) {
        manager.pop(); // pop PauseState
        manager.pop(); // pop GamePlayingState
        return true;
    }
    else if (shouldExit()) {
        manager.pop(); // pop PauseState
        manager.pop(); // pop GamePlayingState
        manager.pop(); // pop menu
        closeWindow = true;
        return true;
    }
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

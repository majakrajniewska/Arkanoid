#include "GameOverState.h"

GameOverState::GameOverState(sf::RenderWindow& window, sf::Font& font, float time, int points, 
    bool win, const sf::Texture* buttonTexture)
	: window(window), font(font), buttonTexture(buttonTexture), time(time), points(points), win(win),
    header(font), timeText(font), pointsText(font)
{
    //header
	if (win) header.setString("Well done");
	else header.setString("Haha Loser");
    header.setFillColor(sf::Color::White);
    header.setCharacterSize(40);
    header.setPosition({ 300.f, 100.f });

    //time
    int minutes = static_cast<int>(time) / 60;
    int seconds = static_cast<int>(time) % 60;

    std::ostringstream timeStream;
    timeStream << "Time: " << std::setw(2) << std::setfill('0') << minutes
        << ":" << std::setw(2) << std::setfill('0') << seconds;

    timeText.setString(timeStream.str());
    timeText.setFillColor(sf::Color::White);
    timeText.setCharacterSize(30);
    timeText.setPosition({ 200.f, 200.f });

    //points
    pointsText.setString("Points: " + std::to_string(points));
    pointsText.setFillColor(sf::Color::White);
    pointsText.setCharacterSize(30);
    pointsText.setPosition({ 400.f, 200.f });

    //create label and set position

    auto createButton = [&](const std::string& text) {
        if (buttonTexture)
            return std::make_unique<Button>(text, *buttonTexture, font, 300, 60);
        else
            return std::make_unique<Button>(text, sf::Color(100, 100, 200), font, 300, 60);
        };

    buttons.push_back(createButton("Try again"));
    buttons.push_back(createButton("Menu"));
    buttons.push_back(createButton("Exit"));

    float startY = 300.f;
    for (size_t i = 0; i < buttons.size(); ++i) {
        buttons[i]->setPosition(window.getSize().x / 2.f - buttons[i]->getWidth() / 2.f, startY + i * 80.f);
    }
}

void GameOverState::handleEvent(sf::Event& event)
{
    if (event.is<sf::Event::MouseButtonPressed>()) {
        sf::Vector2f mousePos = static_cast<sf::Vector2f>(sf::Mouse::getPosition(window));

        if (buttons[0]->isHovered(mousePos)) { // restart
            restartGame = true;
        }
        else if (buttons[1]->isHovered(mousePos)) { // Menu
            goBackToMenu = true;
        }
        else if (buttons[2]->isHovered(mousePos)) { // Exit
            exitRequested = true;
        }
    }
    else if (event.is<sf::Event::Closed>() ||
        (event.is<sf::Event::KeyPressed>() && sf::Keyboard::isKeyPressed(sf::Keyboard::Scancode::Escape))) {
        goBackToMenu = true;
    }
}

void GameOverState::update(float dt)
{
}

void GameOverState::render(sf::RenderWindow& window) {
    window.clear();
    window.draw(header);
    window.draw(timeText);
    window.draw(pointsText);
    for (const auto& btn : buttons)
        btn->draw(window);
    window.display();
}

bool GameOverState::shouldRestartGame() const
{
    return restartGame;
}

bool GameOverState::shouldGoBackToMenu() const
{
    return goBackToMenu;
}

bool GameOverState::shouldExit() const
{
    return exitRequested;
}

void GameOverState::reset()
{
    restartGame = false;
    goBackToMenu = false;
}

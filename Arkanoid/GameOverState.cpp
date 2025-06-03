#include "GameOverState.h"

GameOverState::GameOverState(sf::RenderWindow& window, sf::Font& font, float time, int points,
    bool win, const sf::Texture* buttonTexture)
    : window(window), font(font), buttonTexture(buttonTexture), time(time), points(points), win(win),
    header(font), timeText(font), pointsText(font)
{
    sf::Vector2f viewCenter = window.getView().getCenter();
    float viewWidth = window.getView().getSize().x;
    float viewHeight = window.getView().getSize().y;

    //Header
    header.setString(win ? "Well done" : "Haha Loser");
    header.setCharacterSize(40);
    header.setFillColor(sf::Color::White);
    sf::FloatRect headerBounds = header.getLocalBounds();
    header.setOrigin({ headerBounds.size.x / 2.f, headerBounds.size.y / 2.f });
    header.setPosition({ viewCenter.x, viewCenter.y - viewHeight / 3.f });

    //Time Text
    int minutes = static_cast<int>(time) / 60;
    int seconds = static_cast<int>(time) % 60;
    std::ostringstream timeStream;
    timeStream << "Time: " << std::setw(2) << std::setfill('0') << minutes
        << ":" << std::setw(2) << std::setfill('0') << seconds;

    timeText.setString(timeStream.str());
    timeText.setCharacterSize(30);
    timeText.setFillColor(sf::Color::White);

    //Points Text
    pointsText.setString("Points: " + std::to_string(points));
    pointsText.setCharacterSize(30);
    pointsText.setFillColor(sf::Color::White);

    //Position Time & Points
    float spacing = 50.f;
    sf::FloatRect timeBounds = timeText.getLocalBounds();
    sf::FloatRect pointsBounds = pointsText.getLocalBounds();

    float totalWidth = timeBounds.size.x + pointsBounds.size.x + spacing;

    timeText.setOrigin({timeBounds.position.x, timeBounds.position.y});
    pointsText.setOrigin({ pointsBounds.position.x, pointsBounds.position.y});

    timeText.setPosition({ viewCenter.x - totalWidth / 2.f, viewCenter.y - viewHeight / 4.f });
    pointsText.setPosition({ timeText.getPosition().x + timeBounds.size.x + spacing, timeText.getPosition().y });

    //Buttons
    auto createButton = [&](const std::string& text) {
        if (buttonTexture)
            return std::make_unique<Button>(text, *buttonTexture, font, 300, 60);
        else
            return std::make_unique<Button>(text, sf::Color(100, 100, 200), font, 300, 60);
        };

    buttons.push_back(createButton("Try again"));
    buttons.push_back(createButton("Menu"));
    buttons.push_back(createButton("Exit"));

    float buttonStartY = viewCenter.y + 20.f;
    for (size_t i = 0; i < buttons.size(); ++i) {
        buttons[i]->setPosition(
            viewCenter.x - buttons[i]->getWidth() / 2.f,
            buttonStartY + i * 80.f
        );
    }
}

void GameOverState::handleEvent(sf::Event& event)
{
    if (event.is<sf::Event::MouseButtonPressed>()) {
        sf::Vector2i pixelPos = sf::Mouse::getPosition(window);
        sf::Vector2f worldPos = window.mapPixelToCoords(pixelPos);

        if (buttons[0]->isHovered(worldPos)) { // restart
            restartGame = true;
        }
        else if (buttons[1]->isHovered(worldPos)) { // Menu
            goBackToMenu = true;
        }
        else if (buttons[2]->isHovered(worldPos)) { // Exit
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

bool GameOverState::handleManager(StateManager& manager, bool& restart, bool& closeWindow)
{
    if (shouldRestartGame()) {
        manager.pop(); // pop GameOverState
        manager.pop(); // pop GamePlayingState
        restart = true;
        return true;
    }
    else if (shouldGoBackToMenu()) {
        manager.pop(); // pop GameOverState
        manager.pop(); // pop GamePlayingState
        return true;
    }
    else if (shouldExit()) {
        manager.pop(); // pop GameOverState
        manager.pop(); // pop GamePlayingState
        manager.pop(); // pop menu
        closeWindow = true;
        return true;
    }
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

void GameOverState::setTextPosition(sf::Text& label, float x, float y)
{
    sf::FloatRect textBounds = label.getLocalBounds();
    label.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f, textBounds.position.y + textBounds.size.y / 2.f });
    label.setPosition({ x, y });
}

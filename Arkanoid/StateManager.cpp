#include "StateManager.h"

StateManager::StateManager(unsigned int windowSize)
    : windowSize(windowSize), 
    view(sf::FloatRect({ 0, 0 }, { static_cast<float>(windowSize), static_cast<float>(windowSize) }))
{
    view.setCenter({ windowSize / 2.f, windowSize / 2.f });
}

void StateManager::push(std::unique_ptr<GameState> state) {
    states.push(std::move(state));
}

void StateManager::pop() {
    if (!states.empty()) {
        states.pop();
    }
}

GameState* StateManager::top() {
    return states.empty() ? nullptr : states.top().get();
}

void StateManager::handleEvent(sf::Event& event) {
    if (event.is<sf::Event::Resized>()) {

        sf::RenderWindow* win = states.top()->getWindow();
        unsigned int width = std::max(500u, win->getSize().x);
        unsigned int height = std::max(500u, win->getSize().y);
        if (win->getSize().x != width || win->getSize().y != height) {
            win->setSize({ width, height });
        }

        updateView(*win); 
    }


    if (top()) {
        top()->handleEvent(event);
    }
}

void StateManager::update(float dt) {
    if (top()) {
        top()->update(dt);
    }
}

void StateManager::render(sf::RenderWindow& window) {
    window.setView(view);
    if (top()) {
        top()->render(window);
    }
}

void StateManager::updateView(sf::RenderWindow& window)
{
    auto size = window.getSize();
    float windowWidth = static_cast<float>(size.x);
    float windowHeight = static_cast<float>(size.y);

    float aspectRatio = windowWidth / windowHeight;

    if (aspectRatio > 1.f) {
        // Window is wider than tall - add horizontal borders
        float viewWidth = windowHeight;
        float viewOffset = (windowWidth - viewWidth) / (2.f * windowWidth);
        view.setViewport(sf::FloatRect({ viewOffset, 0.f }, {viewWidth / windowWidth, 1.f
    }));
    }
    else {
        // Window is taller than wide - add vertical borders
        float viewHeight = windowWidth;
        float viewOffset = (windowHeight - viewHeight) / (2.f * windowHeight);
        view.setViewport(sf::FloatRect({ 0.f, viewOffset },{ 1.f, viewHeight / windowHeight }));
    }

    view.setCenter({ windowSize / 2.f, windowSize / 2.f });
    window.setView(view);
}
#include "StateManager.h"

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
    if (top()) {
        top()->render(window);
    }
}

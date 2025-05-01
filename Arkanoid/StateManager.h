#pragma once

#include <stack>
#include <memory>
#include <SFML/Graphics.hpp>
#include "GameState.h"

class StateManager {
public:
    StateManager(unsigned int windowSize = 900);
    void push(std::unique_ptr<GameState> state);
    void pop();
    GameState* top();

    void handleEvent(sf::Event& event);
    void update(float dt);
    void render(sf::RenderWindow& window);

private:
    std::stack<std::unique_ptr<GameState>> states;
    sf::View view;
    unsigned int windowSize;
    void updateView(sf::RenderWindow& window);
};

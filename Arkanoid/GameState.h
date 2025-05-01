#pragma once
#include <SFML/Graphics.hpp>

class GameState {
public:
    virtual ~GameState() = default;

    virtual void handleEvent(sf::Event& event) = 0;
    virtual void update(float dt) = 0;
    virtual void render(sf::RenderWindow& window) = 0;
    virtual bool isTransparent() const { return false; }
    virtual sf::RenderWindow* getWindow() = 0;
};


#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Button {
public:
    // Constructor for image-based button
    Button(const std::string& text, const sf::Texture& texture, const sf::Font& font, unsigned int width, unsigned int height);

    // Constructor for solid color button
    Button(const std::string& text, const sf::Color& bgColor, const sf::Font& font, unsigned int width, unsigned int height);

    void setPosition(float x, float y);
    void draw(sf::RenderWindow& window) const;
    bool isHovered(const sf::Vector2f& mousePos) const;
    void setText(const std::string& newText);

    float getWidth() const;
    float getHeight() const;

private:
    sf::RectangleShape background;
    std::optional<sf::Sprite> backgroundSprite;
    bool usesImage = false;

    sf::Text label;
};


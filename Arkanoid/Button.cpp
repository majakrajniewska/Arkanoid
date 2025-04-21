#include "Button.h"

Button::Button(const std::string& text, const sf::Texture& texture, const sf::Font& font, unsigned int width, unsigned int height)
    : backgroundSprite(sf::Sprite(texture)), usesImage(true), label(font) {
    backgroundSprite->setScale({
        static_cast<float>(width) / texture.getSize().x,
        static_cast<float>(height) / texture.getSize().y });
    label.setString(text);
    label.setCharacterSize(24);
    label.setFillColor(sf::Color::White);
}


Button::Button(const std::string& text, const sf::Color& bgColor, const sf::Font& font, unsigned int width, unsigned int height) 
    : usesImage(false), label(font){
    background.setSize(sf::Vector2f(width, height));
    background.setFillColor(bgColor);
    background.setOutlineColor(sf::Color::White);
    background.setOutlineThickness(2.f);

    label.setString(text);
    label.setCharacterSize(26);
    label.setFillColor(sf::Color::White);
}

void Button::setPosition(float x, float y) {
    sf::Vector2f pos(x, y);

    if (usesImage) {
        backgroundSprite->setPosition(pos);
    }
    else {
        background.setPosition(pos);
    }

    centerLabel(x, y);
}

void Button::draw(sf::RenderWindow& window) const {
    if (usesImage)
        window.draw(*backgroundSprite);
    else
        window.draw(background);
    window.draw(label);
}

bool Button::isHovered(const sf::Vector2f& mousePos) const {
    if (usesImage)
        return backgroundSprite->getGlobalBounds().contains(mousePos);
    else
        return background.getGlobalBounds().contains(mousePos);
}

void Button::setText(const std::string& newText) {
    label.setString(newText);
}

// Helper methods
float Button::getWidth() const {
    return usesImage ? backgroundSprite->getGlobalBounds().size.x : background.getSize().x;
}

float Button::getHeight() const {
    return usesImage ? backgroundSprite->getGlobalBounds().size.y : background.getSize().y;
}

float Button::getX() const
{
    return usesImage ? backgroundSprite->getGlobalBounds().position.x : background.getPosition().x;
}
float Button::getY() const
{
    return usesImage ? backgroundSprite->getGlobalBounds().position.y : background.getPosition().y;
}

void Button::centerLabel(float x, float y)
{
    sf::FloatRect textBounds = label.getLocalBounds();
    float centerX = x + getWidth() / 2.f;
    float centerY = y + getHeight() / 2.f;
    label.setOrigin({ textBounds.position.x + textBounds.size.x / 2.f, textBounds.position.y + textBounds.size.y / 2.f });
    label.setPosition({ centerX, centerY });
}

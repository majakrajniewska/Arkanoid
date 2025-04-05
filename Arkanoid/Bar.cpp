#include "Bar.h"

Bar::Bar(float width, float height, float newSpeed, unsigned int SCREEN_W, unsigned int SCREEN_H){
	shape.setSize({ width, height });
	shape.setFillColor(sf::Color::Cyan);
	shape.setPosition({ SCREEN_W / 2.f, SCREEN_H - SCREEN_H / 5.f });

	speed = newSpeed;
}

void Bar::update(const sf::RenderWindow& window, float direction) {
	sf::Vector2f pos = shape.getPosition();
	float newX = pos.x + speed * direction;
	float barWidth = shape.getSize().x;
	float windowWidth = static_cast<float>(window.getSize().x);

	// Clamp newX between 0 and window width - bar width
	newX = std::max(0.f, std::min(newX, windowWidth - barWidth));
	shape.setPosition({ newX, pos.y });
}
void Bar::draw(sf::RenderWindow& window) const {
	window.draw(shape);
}

sf::FloatRect Bar::getBounds() const
{
	return shape.getGlobalBounds();
}


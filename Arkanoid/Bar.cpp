#include "Bar.h"

Bar::Bar(float width, float height, float newSpeed, unsigned int SCREEN_W, unsigned int SCREEN_H){
	shape.setSize({ width, height });
	shape.setFillColor(sf::Color::Cyan);
	shape.setPosition({ SCREEN_W / 2.f, SCREEN_H - SCREEN_H / 5.f });

	speed = newSpeed;
}

void Bar::update(const sf::RenderWindow& window, float direction) {
	shape.move({ speed*direction, 0 });
}
void Bar::draw(sf::RenderWindow& window) const {
	window.draw(shape);
}

sf::FloatRect Bar::getBounds() const
{
	return shape.getGlobalBounds();
}


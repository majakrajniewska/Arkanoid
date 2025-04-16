#include "Bumper.h"

Bumper::Bumper(float width, float height, float speed, unsigned int SCREEN_W, unsigned int SCREEN_H) 
	: speed(speed){
	shape.setSize({ width, height });
	shape.setFillColor(sf::Color::Cyan);
	shape.setPosition({ SCREEN_W / 2.f, SCREEN_H - SCREEN_H / 5.f });
	moving = false;
}

void Bumper::update(const unsigned int windowWidth, float direction) {
	moving = true;
	sf::Vector2f pos = shape.getPosition();
	float newX = pos.x + speed * direction;
	float BumperWidth = shape.getSize().x;

	// Clamp newX between 0 and window width - Bumper width
	newX = std::max(0.f, std::min(newX, windowWidth - BumperWidth));
	shape.setPosition({ newX, pos.y });
}
void Bumper::draw(sf::RenderWindow& window) {
	moving = false;
	window.draw(shape);
}

sf::FloatRect Bumper::getBounds() const
{
	return shape.getGlobalBounds();
}

bool Bumper::isMoving() const
{
	return moving;
}


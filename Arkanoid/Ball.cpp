#include "Ball.h"

Ball::Ball(float radius, unsigned int SCREEN_W, unsigned int SCREEN_H) {
	shape.setRadius(radius);
	shape.setFillColor(sf::Color::Magenta);
	startPosition = { SCREEN_W / 2.f, SCREEN_H / 2.f };
	shape.setPosition(startPosition);
	velocity = { -5.f, -4.f};
}

void Ball::update(const sf::RenderWindow& window, const Bar& bar) {
	shape.move(velocity);
	checkCollision(window, bar);
}

void Ball::checkCollision(const sf::RenderWindow& window, const Bar& bar) {
	sf::FloatRect ballBounds = shape.getGlobalBounds();

	// Check collision with window bounds
	if (ballBounds.position.x <= 0 || ballBounds.position.x + ballBounds.size.x >= window.getSize().x) {
		velocity.x = -velocity.x; // Reverse horizontal direction
	}
	if (ballBounds.position.y <= 0 || ballBounds.position.y + ballBounds.size.y >= window.getSize().y) {
		velocity.y = -velocity.y; // Reverse vertical direction
	}

	//check collision with the bar
	if (ballBounds.findIntersection(bar.getBounds())) {
		velocity.y = -velocity.y;
	}
}

void Ball::draw(sf::RenderWindow& window) const {
	window.draw(shape);
}



#include "Block.h"

Block::Block(float width, float height, float x, float y, int lives) : lives(lives)
{
	shape.setSize({ width, height });
	shape.setPosition({ x, y});
	shape.setOutlineThickness(5);
	shape.setOutlineColor(sf::Color::White);
	updateColors(lives);
}

void Block::draw(sf::RenderWindow& window)
{
	if (lives > 0) {
		updateColors(lives);
		window.draw(shape);
	}
}

sf::FloatRect Block::getBounds() const
{
	return shape.getGlobalBounds();
}

int Block::getLives() const
{
	return lives;
}

void Block::updateColors(int lives)
{
	switch (lives) {
	case 1: shape.setFillColor(sf::Color::Green); break;
	case 2: shape.setFillColor(sf::Color::Yellow); break;
	case 3: shape.setFillColor(sf::Color::Red);
	}
}

void Block::decrementLives()
{
	lives--;
}

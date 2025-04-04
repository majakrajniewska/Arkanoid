#pragma once
#include <SFML/Graphics.hpp>
class Block
{
public:
	Block(float width, float height, float x, float y, int lives);
	void draw(sf::RenderWindow& window);
	sf::FloatRect getBounds() const;
	int getLives() const;
	void updateColors(int lives);
	void decrementLives();

private:
	sf::RectangleShape shape;
	int lives;
};


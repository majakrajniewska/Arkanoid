#pragma once
#include <SFML/Graphics.hpp>
class Bumper
{
public:
	Bumper(float width, float height, float newSpeed, unsigned int SCREEN_W, unsigned int SCREEN_H);
	void update(const unsigned int windowWidth, float direction);
	void draw(sf::RenderWindow& window);
	sf::FloatRect getBounds() const;
	bool isMoving() const;

private:
	sf::RectangleShape shape;
	float speed;
	bool moving;
};


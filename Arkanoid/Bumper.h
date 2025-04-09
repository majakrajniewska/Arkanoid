#pragma once
#include <SFML/Graphics.hpp>
class Bumper
{
public:
	Bumper(float width, float height, float newSpeed, unsigned int SCREEN_W, unsigned int SCREEN_H);
	void update(const sf::RenderWindow& window, float direction);
	void draw(sf::RenderWindow& window) const;
	sf::FloatRect getBounds() const;

private:
	sf::RectangleShape shape;
	float speed;
};


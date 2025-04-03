#include <SFML/Graphics.hpp>
#include "Bar.h"
class Ball
{
public:
	Ball(float radius, unsigned int SCREEN_W, unsigned int SCREEN_H);
	void update(const sf::RenderWindow& window, const Bar& bar);
	void draw(sf::RenderWindow& window) const;

private:
	sf::CircleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f startPosition;

	void checkCollision(const sf::RenderWindow& window, const Bar& bar);
};


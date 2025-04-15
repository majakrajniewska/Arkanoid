#include <SFML/Graphics.hpp>
#include "Bumper.h"
#include "Block.h"
#include "GameHandler.h"

class Ball
{
public:
	Ball(float radius, unsigned int SCREEN_W, unsigned int SCREEN_H);
	void update(sf::RenderWindow& window, GameHandler& gh, const Bumper& bumper, std::vector<Block*>& blocks);
	void draw(sf::RenderWindow& window) const;

private:
	sf::CircleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f startPosition;

	void checkCollision(sf::RenderWindow& window, GameHandler& gh, const Bumper& bumper, std::vector<Block*>& blocks);
	void bounceX();
	void bounceY();
};


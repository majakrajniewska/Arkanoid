#include <SFML/Graphics.hpp>
#include "Bumper.h"
#include "Block.h"
#include "GameHandler.h"
#include "BallSpeed.h"


class Ball
{
public:
	Ball(float radius, unsigned int SCREEN_W, unsigned int SCREEN_H, BallSpeed speed);
	void update(sf::RenderWindow& window, GameHandler& gh, const Bumper& bumper, std::vector<std::unique_ptr<Block>>& blocks);
	void draw(sf::RenderWindow& window) const;
	void reset();

private:
	sf::CircleShape shape;
	sf::Vector2f velocity;
	sf::Vector2f startPosition;
	BallSpeed speed;

	void checkCollision(sf::RenderWindow& window, GameHandler& gh, const Bumper& bumper, std::vector<std::unique_ptr<Block>>& blocks);
	void bounceX();
	void bounceY();

	void generateVelocity();
};


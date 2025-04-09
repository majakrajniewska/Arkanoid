#include "Ball.h"
#include "Block.h"

Ball::Ball(float radius, unsigned int SCREEN_W, unsigned int SCREEN_H) {
	shape.setRadius(radius);
	shape.setFillColor(sf::Color::Magenta);
	startPosition = { SCREEN_W / 2.f, SCREEN_H / 2.f };
	shape.setPosition(startPosition);
	velocity = { -5.f, -4.f};
}
void Ball::bounceX()
{
	velocity.x = -velocity.x;
}

void Ball::bounceY()
{
	velocity.y = -velocity.y;
}
void Ball::update(const sf::RenderWindow& window, const Bumper& bumper, std::vector<Block*>& blocks) {
	shape.move(velocity);
	checkCollision(window, bumper, blocks);
}

void Ball::checkCollision(const sf::RenderWindow& window, const Bumper& bumper, std::vector<Block*>& blocks) {
	sf::FloatRect ballBounds = shape.getGlobalBounds();

	// Check collision with window bounds
	if (ballBounds.position.x <= 0 || ballBounds.position.x + ballBounds.size.x >= window.getSize().x) {
		bounceX();
	}
	if (ballBounds.position.y <= 0 || ballBounds.position.y + ballBounds.size.y >= window.getSize().y) {
		bounceY();
	}

	//check collision with the Bumper
	if (ballBounds.findIntersection(bumper.getBounds())) {
		velocity.y = -velocity.y;
	}

	sf::Vector2f ballCenter = ballBounds.position + ballBounds.size / 2.f;

	//check collision with blocks
    for (auto it = blocks.begin(); it != blocks.end(); ) {
        Block* block = *it;

        if (ballBounds.findIntersection(block->getBounds())) {
            block->decrementLives();

            sf::FloatRect blockBounds = block->getBounds();
            sf::Vector2f blockCenter = blockBounds.position + blockBounds.size / 2.f;

            // Calculate delta between centers
            float dx = ballCenter.x - blockCenter.x;
            float dy = ballCenter.y - blockCenter.y;

            float combinedHalfWidths = (ballBounds.size.x + blockBounds.size.x) / 2.f;
            float combinedHalfHeights = (ballBounds.size.y + blockBounds.size.y) / 2.f;

            float overlapX = combinedHalfWidths - std::abs(dx);
            float overlapY = combinedHalfHeights - std::abs(dy);

            // Bounce in the direction of least overlap
            if (overlapX < overlapY) {
                bounceX();
            }
            else {
                bounceY();
            }

            // If block is destroyed, delete and remove it
            if (block->getLives() <= 0) {
                it = blocks.erase(it);
                delete block;
            }
            else {
                ++it;
            }

            break; // Only one block collision per frame
        }
        else {
            ++it;
        }
    }
}

void Ball::draw(sf::RenderWindow& window) const {
	window.draw(shape);
}



#include "Ball.h"
#include "Block.h"
#include "GameHandler.h"

Ball::Ball(float radius, unsigned int SCREEN_W, unsigned int SCREEN_H) {
	shape.setRadius(radius);
	shape.setFillColor(sf::Color::Magenta);
	startPosition = { SCREEN_W / 2.f, SCREEN_H - SCREEN_H / 3.f };
    shape.setPosition(startPosition);
    velocity = {4.f, -5.f};
}
void Ball::bounceX()
{
	velocity.x = -velocity.x;
}

void Ball::bounceY()
{
	velocity.y = -velocity.y;
}

void Ball::update(sf::RenderWindow& window, GameHandler& gh, const Bumper& bumper, std::vector<Block*>& blocks) {
	shape.move(velocity);
	checkCollision(window, gh, bumper, blocks);
}

void Ball::checkCollision(sf::RenderWindow& window, GameHandler& gh, const Bumper& bumper, std::vector<Block*>& blocks) {
	sf::FloatRect ballBounds = shape.getGlobalBounds();

	// Check collision with window bounds
	if (ballBounds.position.x <= 0 || ballBounds.position.x + ballBounds.size.x >= window.getSize().x) {
		bounceX();
	}
	if (ballBounds.position.y <= 0 || ballBounds.position.y + ballBounds.size.y >= window.getSize().y) {
        if (ballBounds.position.y + ballBounds.size.y >= window.getSize().y) {
            gh.decrementLives();
            if (gh.checkLoose()) gh.loose(window);
            shape.setPosition(startPosition);
        }
		bounceY();
	}

	//check collision with the Bumper
	if (ballBounds.findIntersection(bumper.getBounds())) {
        sf::FloatRect bumperBounds = bumper.getBounds();
        sf::Vector2f ballCenter = ballBounds.position + ballBounds.size / 2.f;
        sf::Vector2f bumperCenter = bumperBounds.position + bumperBounds.size / 2.f;

        float dx = ballCenter.x - bumperCenter.x;
        float dy = ballCenter.y - bumperCenter.y;

        float absDX = std::abs(dx);
        float absDY = std::abs(dy);

        float halfW = (ballBounds.size.x + bumperBounds.size.x) / 2.f;
        float halfH = (ballBounds.size.y + bumperBounds.size.y) / 2.f;

        if (absDX > bumperBounds.size.x / 2.f) {
            //Side hit
            velocity.x = -velocity.x;
            velocity.y = std::abs(velocity.y); // always force down after side bump

            if (dx > 0) {
                shape.setPosition({ bumperBounds.position.x + bumperBounds.size.x, shape.getPosition().y });
            }
            else {
                shape.setPosition({ bumperBounds.position.x - ballBounds.size.x, shape.getPosition().y });
            }
        }
        else {
            //Top hit
            velocity.y = -std::abs(velocity.y);

            if (bumper.isMoving()) {
                velocity.x = std::clamp(velocity.x * 1.2f, -8.f, 8.f);
            }

            // Push ball above the bumper
            shape.setPosition({ shape.getPosition().x, bumperBounds.position.y - ballBounds.size.y });
        }
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
            //if there is no block left - win
            if (blocks.empty()) gh.win(window);
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



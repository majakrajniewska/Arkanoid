#include "Ball.h"
#include "Block.h"
#include "GameHandler.h"
#include <cstdlib>
#include <ctime>
#include <cmath>

Ball::Ball(float radius, unsigned int SCREEN_W, unsigned int SCREEN_H, BallSpeed speed) : speed(speed) {
	shape.setRadius(radius);
	shape.setFillColor(sf::Color::Magenta);
	startPosition = { SCREEN_W / 2.f, SCREEN_H - SCREEN_H / 3.f };
    shape.setPosition(startPosition);
    generateVelocity();
}
void Ball::bounceX()
{
	velocity.x = -velocity.x;
}

void Ball::bounceY()
{
	velocity.y = -velocity.y;
}

void Ball::generateVelocity()
{
    float s;
    switch (speed) {
    case BallSpeed::Slow: s = 5.f; break;
    case BallSpeed::Normal: s = 8.f; break;
    case BallSpeed::Fast: s = 12.f;
    }
    float min = -30.f;
    float max = -150.f;
    float alfa = min + static_cast<float>(std::rand()) / RAND_MAX * (max - min);
    float alfaRadians = alfa * (3.14159265f / 180.0f);
    velocity = {s*std::cos(alfaRadians), s*std::sin(alfaRadians)};
}

void Ball::update(sf::RenderWindow& window, GameHandler& gh, const Bumper& bumper, std::vector<std::unique_ptr<Block>>& blocks) {
    shape.move(velocity);
    checkCollision(window, gh, bumper, blocks);
}

void Ball::checkCollision(sf::RenderWindow& window, GameHandler& gh, const Bumper& bumper, std::vector<std::unique_ptr<Block>>& blocks) {
	sf::FloatRect ballBounds = shape.getGlobalBounds();

	// Check collision with window bounds
	if (ballBounds.position.x <= 0 || ballBounds.position.x + ballBounds.size.x >= window.getSize().x) {
		bounceX();
	}
	if (ballBounds.position.y <= 0) {
		bounceY();
	}
    if (ballBounds.position.y + ballBounds.size.y >= window.getSize().y) {
        gh.decrementLives();
        reset();
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
        Block* block = it->get();
        if (ballBounds.findIntersection(block->getBounds())) {
            block->decrementLives();

            sf::FloatRect blockBounds = block->getBounds();
            sf::Vector2f blockCenter = blockBounds.position + blockBounds.size / 2.f;

            float dx = ballCenter.x - blockCenter.x;
            float dy = ballCenter.y - blockCenter.y;

            float combinedHalfWidths = (ballBounds.size.x + blockBounds.size.x) / 2.f;
            float combinedHalfHeights = (ballBounds.size.y + blockBounds.size.y) / 2.f;

            float overlapX = combinedHalfWidths - std::abs(dx);
            float overlapY = combinedHalfHeights - std::abs(dy);

            if (overlapX < overlapY) {
                bounceX();
            }
            else {
                bounceY();
            }

            if (block->getLives() <= 0) {
                it = blocks.erase(it); // unique_ptr auto-deletes
            }
            else {
                ++it;
            }

            if (blocks.empty()) {
                //gh.win(window);
            }

            break; // One block per frame
        }
        else {
            ++it;
        }
    }
}

void Ball::draw(sf::RenderWindow& window) const {
	window.draw(shape);
}

void Ball::reset()
{
    shape.setPosition(startPosition);
    generateVelocity();
}



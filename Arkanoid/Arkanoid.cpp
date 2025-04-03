#include <SFML/Graphics.hpp>

int main()
{
    unsigned int SCREEN_HEIGHT = 900;
    unsigned int SCREEN_WIDTH = 900;
    sf::RenderWindow* window = new sf::RenderWindow(sf::VideoMode({ SCREEN_WIDTH, SCREEN_HEIGHT }), "ARKANOID");
    sf::CircleShape ball(30.f);
    ball.setFillColor(sf::Color::Green);
    ball.setOrigin(ball.getGeometricCenter());
    ball.setPosition({ SCREEN_WIDTH / 2.f, SCREEN_HEIGHT / 2.f });

    sf::Vector2f velocity = { 5.f, 4.f };

    window->setFramerateLimit(60);

    while (window->isOpen())
    {
        while (const std::optional event = window->pollEvent())
        {
            //Close window
            if (event->is<sf::Event::Closed>())
                window->close();
            //Keys pressed
            else if (const auto* keyPressed = event->getIf<sf::Event::KeyPressed>()) {
                //Escape
                if (keyPressed->scancode == sf::Keyboard::Scancode::Escape)
                    window->close();
            }
        }

        ball.move(velocity);
        sf::FloatRect ballBounds = ball.getGlobalBounds();

        // Check collision with window bounds
        if (ballBounds.position.x <= 0 || ballBounds.position.x + ballBounds.size.x >= window->getSize().x) {
            velocity.x = -velocity.x; // Reverse horizontal direction
        }
        if (ballBounds.position.y <= 0 || ballBounds.position.y + ballBounds.size.y >= window->getSize().y) {
            velocity.y = -velocity.y; // Reverse vertical direction
        }
        window->clear();
        window->draw(ball);
        window->display();
    }
}
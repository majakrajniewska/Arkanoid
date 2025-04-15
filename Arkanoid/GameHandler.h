#pragma once
#include <SFML/Graphics.hpp>
class GameHandler
{
public:
	GameHandler(int lives);
	void win(sf::RenderWindow& window);
	void loose(sf::RenderWindow& window);
	bool checkLoose();
	void decrementLives();
private:
	int lives;
	int points;

};


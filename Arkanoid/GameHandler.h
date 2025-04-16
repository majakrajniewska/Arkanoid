#pragma once
#include <SFML/Graphics.hpp>
class GameHandler
{
public:
	GameHandler(int lives);
	void win(sf::RenderWindow& window);
	void lose(sf::RenderWindow& window);
	bool checkLose();
	void decrementLives();
private:
	int lives;
	int points;

};


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
	int addPoints(int p);
private:
	int lives;
	int points;

};


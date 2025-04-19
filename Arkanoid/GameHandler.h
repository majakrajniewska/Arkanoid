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
	float addPoints(float p);
	float getPoints();
private:
	int lives;
	float points;

};


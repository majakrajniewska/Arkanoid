#pragma once
#include <SFML/Graphics.hpp>
class GameHandler
{
public:
	GameHandler(int lives);
	bool checkLose();
	void decrementLives();
	float addPoints(float p);
	float getPoints();
	float getLives();
private:
	int lives;
	float points;

};


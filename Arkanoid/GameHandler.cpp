#include "GameHandler.h"

GameHandler::GameHandler(int lives) : lives(lives), points(0.f)
{
}

void GameHandler::win(sf::RenderWindow& window)
{
	window.close();
}

void GameHandler::lose(sf::RenderWindow& window)
{
	window.close();
}

bool GameHandler::checkLose()
{
	return lives == 0.f;
}

void GameHandler::decrementLives()
{
	lives--;
}

float GameHandler::addPoints(float p)
{
	return points+=p;
}

float GameHandler::getPoints()
{
	return points;
}



#include "GameHandler.h"

GameHandler::GameHandler(int lives) : lives(lives), points(0)
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
	return lives == 0;
}

void GameHandler::decrementLives()
{
	lives--;
}

int GameHandler::addPoints(int p)
{
	return points+=p;
}



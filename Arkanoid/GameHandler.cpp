#include "GameHandler.h"

GameHandler::GameHandler(int lives) : lives(lives), points(0)
{
}

void GameHandler::win(sf::RenderWindow& window)
{
	window.close();
}

void GameHandler::loose(sf::RenderWindow& window)
{
	window.close();
}

bool GameHandler::checkLoose()
{
	return lives == 0;
}

void GameHandler::decrementLives()
{
	lives--;
}


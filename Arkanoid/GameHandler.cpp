#include "GameHandler.h"

GameHandler::GameHandler(int lives) : lives(lives), points(0.f)
{
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

float GameHandler::getLives()
{
	return lives;
}



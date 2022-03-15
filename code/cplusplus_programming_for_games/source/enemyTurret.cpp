#include "enemyTurret.h"


void enemyTurret::moveTowardsPlayer(float playerY, float playerX, float playerRotation)
{
	playerY = playerY;
	playerX = playerX;


	rotation += 0.5;

	//std::cout << rotation;
	SDL_Point center = { rect.w / 2, rect.h / 2 };
	SetRotation(rotation, &center);


	/*
	if (getY() > playerY)
	{
		SetPosition(getY() - moveSpeed, getX());
	}
	else if (getY() < playerY)
	{
		SetPosition(getY() + moveSpeed, getX());
	}
	else if (getX() > playerX)
	{
		SetPosition(getY(), getX() - moveSpeed);
	}
	else if (getX() < playerX)
	{
		SetPosition(getY(), getX() + moveSpeed);
	}*/

}
#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "Sprite.h"

using namespace std;

#pragma once
class enemyTurret : public Sprite
{
public:


	enemyTurret(string file, SDL_Renderer* sdlRenderer) : Sprite(file, sdlRenderer)
	{
		renderer = sdlRenderer;		
	}

	void moveTowardsPlayer(float playerY, float playerX, float playerRotation);

	float getAng() const
	{
		//return rotation angle
		return getAngle();
	}
	float getY() const
	{
		//return rotation angle
		return getYPos();
	}
	float getX() const
	{
		//return rotation angle
		return getXPos();
	}


private:

	SDL_Surface* surface;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect rect;

	float rotation;

	float moveSpeed = 1;
};


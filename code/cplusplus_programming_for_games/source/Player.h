#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Sprite.h"
#include "SoundPlayer.h"

#define PI 3.14159265


class Player
{

public:
	Player(SDL_Renderer* sdlRenderer, int _windowWidth, int _windowHeight);
	void init();
	void render();
	void update();
	void clean();

	//initialize sound player
	//soundPlayer = new SoundPlayer();
	void moveRight()
	{
		rotation += 3;

		/*
		portion.x += speedConstant;

		if (portion.x + portion.w >= windowWidth)
		{
			//soundPlayer->PlaySound(Sounds::BELL);
			portion.x = windowWidth - portion.w;
		}*/
	}

	void moveLeft()
	{
		rotation -= 3;
		/*
		portion.x -= speedConstant;
		if (portion.x <= 0)
		{
			portion.x = 0;
		}
		*/

	}
	void moveUp()
	{
		IsmoveUp = true;
		int lastX = portion.x;
		int lastY = portion.y;

		//std::cout << lastX && " " && lastY;
		portion.x += sin(rotation * PI / 180.0f) * speedConstant;

		portion.y -= cos(rotation * PI / 180.0f) * speedConstant;

		boundingSphere->x = portion.x;
		boundingSphere->y = portion.y;
		/*portion.y -= speedConstant;
		if (portion.y <= 0)
		{
			portion.y = 0;
		}*/
	}
	void moveDown()
	{
		IsmoveUp = false;
		int lastX = portion.x;
		int lastY = portion.y;
		
		portion.x -= sin(rotation * PI / 180.0f) * speedConstant;

		portion.y += cos(rotation * PI / 180.0f) * speedConstant;

		boundingSphere->x = portion.x;
		boundingSphere->y = portion.y;
		/*
		portion.y += speedConstant;
		if (portion.y + portion.h >= windowHeight)
		{
			portion.y = windowHeight - portion.h;
		}*/
	}

	float getAngle() const
	{
		//return rotation angle
		return rotation;
	}
	float getYPos() const
	{
		//return rotation angle
		return portion.y + portion.h / 2;
	}
	float getXPos() const
	{
		//return rotation angle
		return portion.x + portion.w / 2;
	}

	bool SphereCollision(Sprite& other)
	{
		return boundingSphere->CollisionWithSphere(*other.boundingSphere);
	}

	void setXY(int x, int y);


	SDL_Rect portion;

	float lastX;
	float lastY;
	bool IsmoveUp;

	Sphere* boundingSphere;

private:
	int x = 0;
	int y = 0;

	const int speedConstant = 10;

	int windowWidth = 0;
	int windowHeight = 0;

	float rotation = 0;


	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
};


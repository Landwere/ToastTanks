#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <math.h>
#include <algorithm>

#include "Player.h"
#include "SoundPlayer.h"

#define PI 3.14159265

using namespace std;

class BulletManager
{
public: 
	BulletManager(SDL_Renderer* renderer, Player* player);
	
	void init();
	void update();
	void draw();
	void clean();


	void proccessInput()
	{
			if (SDL_GetTicks() - lastShot > SHOOT_TIMER_MS)
			{
				bullets.push_back(Bullet{ player->getXPos(), player->getYPos(), player->getAngle(), 0.0f, Sphere(player->getXPos(), player->getYPos(), 10) });
				lastShot = SDL_GetTicks();
				secondShotLoaded = true;
				soundPlayer->PlaySound(4, false);
			}
			else if (secondShotLoaded)
			{
				bullets.push_back(Bullet{ player->getXPos(), player->getYPos(), player->getAngle(), 0.0f, Sphere(player->getXPos(), player->getYPos(), 10) });
				lastShot = SDL_GetTicks();
				secondShotLoaded = false;
				soundPlayer->PlaySound(4, false);
			}
	}

	bool SphereCollision(Sprite& other)
	{
		for (auto& bullet : bullets)
		{
			if (bullet.boundingSphere.CollisionWithSphere(*other.boundingSphere))
				return true;

		}
		return false;
	}

	struct Bullet
	{
		float x, y, rotation, distance;
		Sphere boundingSphere;
	};

private:
	SDL_Renderer * renderer = nullptr;
	SDL_Texture * bulletTexture;
	vector<Bullet> bullets;
	//reference to the player to get the angle of fire
	Player * player;

	Sphere* boundingSphere;

	SDL_Rect UI1portion;
	SDL_Rect UI2portion;

	SDL_Texture* bulletUI1Texture;
	SDL_Texture* bulletUI2Texture;

	SoundPlayer* soundPlayer;

	//time between shots
	const int SHOOT_TIMER_MS = 2000;
	//speed of bullet (pixels per frame)
	const float BULLET_VELOCITY = 5.0;
	unsigned int lastShot = 0;
	bool secondShotLoaded = true;
};




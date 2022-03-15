#pragma once
#include <SDL.h>
#include <SDL_image.h>

#include <vector>
#include <math.h>
#include <algorithm>

#include "enemyTurret.h"
#include "SoundPlayer.h"
#include "Player.h"

#define PI 3.14159265

using namespace std;

class EnemyBulletManager
{
public:
	EnemyBulletManager(SDL_Renderer* renderer, enemyTurret* enemy);

	void init();
	void update();
	void draw();
	void clean();


	void proccessInput()
	{
		if (SDL_GetTicks() - lastShot > SHOOT_TIMER_MS)
		{
			bullets.push_back(Bullet{ enemy->getX(), enemy->getY(), enemy->getAng() + 10, 0.0f, Sphere(enemy->getXPos(), enemy->getYPos(), 10), SDL_Rect() });
			
			lastShot = SDL_GetTicks();
			soundPlayer->PlaySound(4, false);
		}
	}

	bool SphereCollision(Player other)
	{
		SDL_Rect playerRect = other.portion;
		SDL_Rect result;
		
		for (auto& bullet : bullets)
		{
		
			//cout << bullet.rect.h;
			if (SDL_IntersectRect(&bullet.rect, &playerRect, &result))
			{
				cout << "HIT";
				return true;
			}
		}
		return false;
	}

	struct Bullet
	{
		float x, y, rotation, distance;
		Sphere boundingSphere;
		SDL_Rect rect;
	};

private:
	SDL_Renderer * renderer = nullptr;
	SDL_Texture * bulletTexture;
	vector<Bullet> bullets;
	//reference to the enemy to get the angle of fire
	enemyTurret * enemy;

	Sphere* boundingSphere;

	SoundPlayer* soundPlayer;

	//time between shots
	const int SHOOT_TIMER_MS = 2000;
	//speed of bullet (pixels per frame)
	const float BULLET_VELOCITY = 5.0;
	unsigned int lastShot = 0;
	bool secondShotLoaded = true;
};




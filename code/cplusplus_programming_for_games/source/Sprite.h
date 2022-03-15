#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
using namespace std;
struct  Sphere
{
	friend class Sprite;
	friend class Player;
	friend class enemyTurret;
	friend class BulletManager;
	friend class EnemyBulletManager;

	Sphere(int x, int y, int radius) : x(x), y(y), radius(radius) {};
		bool CollisionWithSphere(Sphere& s) const
	{
		int diffX = s.x > x ? s.x - x : x - s.x;
		int diffY = s.y > y ? s.y - y : y - s.y;
		int vectorLength = sqrt(diffX * diffX + diffY * diffY);
		return vectorLength < (radius + s.radius);
		return false;
	}

private:
	int x, y;
	int radius;
};

struct Sprite
{
	friend class enemyTurret;
public:
	Sprite()
	{

	}
	Sprite(string file, SDL_Renderer* sdlRenderer)
	{
		renderer = sdlRenderer;

		//this->surface = SDL_LoadBMP(file.c_str());
		this->surface = IMG_Load(file.c_str());
		texture = SDL_CreateTextureFromSurface(renderer, surface);
		if (this->surface == NULL)
		{
			//std::cout << "Unable to load image";
		}
		this->rect.x = 1;
		this->rect.y = 1;

		this->rect.w = surface->w;
		this->rect.h = surface->h;

		rect.w = 60;
		rect.h = 60;

		

		boundingSphere = new Sphere(rect.x + (rect.w / 2), rect.y + (rect.h / 2), rect.w / 2);
		visible = true;

	}

	virtual ~Sprite()
	{
		SDL_FreeSurface(this->surface);
		//SAFERELEASE(boundingSphere);
	}

	void SetPosition(float x, float y)
	{
		this->rect.x = x;
		this->rect.y = y;
		this->boundingSphere->x = x;
		this->boundingSphere->y = y;
	}

	void SetRotation(float angle, SDL_Point* center)
	{
		
		rotation = angle;
	}

	void Render()
	{
		if (visible)
		{
			//SDL_RenderCopy(renderer, texture, 0, &rect);
			SDL_Point sprcenter = { rect.w / 2, rect.h / 2 };
			SDL_RenderCopyEx(renderer, texture, 0, &rect, rotation, &sprcenter, SDL_FLIP_NONE);
		}
		/*
		if (this->visible)
		{
			//SDL_BlitSurface(surface, NULL, renderFrame, &rect);
			
		}*/
	}

	bool SphereCollision(Sprite& other)
	{
		return boundingSphere->CollisionWithSphere(*other.boundingSphere);
	}

	void SetVisible(bool visible) { this->visible = visible; }

	int getX()
	{
		return rect.x;
	}

	int getY()
	{
		return rect.y;
	}

	float getAngle() const
	{
		//return rotation angle
		return rotation;
	}
	float getYPos() const
	{
		//return rotation angle
		return rect.y + rect.h / 2;
	}
	float getXPos() const
	{
		//return rotation angle
		return rect.x + rect.w / 2;
	}

	Sphere* boundingSphere;

	bool visible;

private:

	
	SDL_Surface * surface;
	SDL_Renderer* renderer = nullptr;
	SDL_Texture* texture = nullptr;
	SDL_Rect rect;

	float rotation = 0;
};


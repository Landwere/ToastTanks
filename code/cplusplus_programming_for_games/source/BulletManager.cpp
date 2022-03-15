#include "BulletManager.h"

BulletManager::BulletManager(SDL_Renderer* renderer, Player* player) : renderer(renderer), player(player) {}

void BulletManager::init()
{
	//load bullet texture
	SDL_Surface* surface = IMG_Load("assets\\Toast.png");
	this->bulletTexture = SDL_CreateTextureFromSurface(this->renderer, surface);

	bulletUI1Texture = SDL_CreateTextureFromSurface(renderer, surface);
	bulletUI2Texture = SDL_CreateTextureFromSurface(renderer, surface);

	SDL_FreeSurface(surface);

	UI1portion.y = 50;
	UI2portion.y = 50;
	UI2portion.x = 60;
	UI1portion.w = 40;
	UI1portion.h = 40;
	UI2portion.w = 40;
	UI2portion.h = 40;

	secondShotLoaded = false;

	soundPlayer = new SoundPlayer();
	soundPlayer->init();

	
}

void BulletManager::update()
{

	for (auto& b : bullets)
	{
		b.x += sin(b.rotation * PI / 180.0f) * BULLET_VELOCITY;
		b.y -= cos(b.rotation * PI / 180.0f) * BULLET_VELOCITY;
		b.distance += BULLET_VELOCITY;
		b.boundingSphere.x = b.x;
		b.boundingSphere.y = b.y;
	}

	if (SDL_GetTicks() - lastShot > SHOOT_TIMER_MS)
	{
		//secondShotLoaded = true;

	}


	//Remove bullet after 1000 pixels traveled
	auto remove = std::remove_if(bullets.begin(), bullets.end(), [](const Bullet& b) {return b.distance > 1000; });
	bullets.erase(remove, bullets.end());
}

void BulletManager::draw()
{
	SDL_Point center = { 5, 5 };
	for (auto& b : bullets)
	{
		SDL_Rect dest = { b.x, b.y, 20, 20 };
		b.boundingSphere = Sphere(b.x + (20 / 2), b.y + (20 / 2), 20 / 2);
		SDL_RenderCopyEx(renderer, bulletTexture, 0, &dest, b.rotation, &center, SDL_FLIP_NONE);
	}

	if (secondShotLoaded)
	{
		SDL_RenderCopy(renderer, bulletUI1Texture, NULL, &UI1portion);
	
	}
	if (SDL_GetTicks() - lastShot > SHOOT_TIMER_MS)
	{
		SDL_RenderCopy(renderer, bulletUI1Texture, NULL, &UI1portion);
		SDL_RenderCopy(renderer, bulletUI2Texture, NULL, &UI2portion);
	}

}

void BulletManager::clean()
{
	SDL_DestroyTexture(this->bulletTexture);
	SDL_DestroyTexture(this->bulletUI1Texture);
	SDL_DestroyTexture(this->bulletUI2Texture);
	delete soundPlayer;

}
#include "EnemyBulletManager.h"

EnemyBulletManager::EnemyBulletManager(SDL_Renderer* renderer, enemyTurret* enemy) : renderer(renderer), enemy(enemy) {}

void EnemyBulletManager::init()
{
	
	//load bullet texture
	SDL_Surface* surface = IMG_Load("assets\\bullet2.png");
	this->bulletTexture = SDL_CreateTextureFromSurface(this->renderer, surface);

	SDL_FreeSurface(surface);
	

	soundPlayer = new SoundPlayer();
	soundPlayer->init();

	
}

void EnemyBulletManager::update()
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

void EnemyBulletManager::draw()
{
	SDL_Point center = { 5, 5 };
	for (auto& b : bullets)
	{
		SDL_Rect dest = { b.x, b.y, 25, 25 };
		b.rect = dest;
		b.boundingSphere = Sphere(b.x + (20 / 2), b.y + (20 / 2), 20 / 2);
		SDL_RenderCopyEx(renderer, bulletTexture, 0, &dest, b.rotation, &center, SDL_FLIP_NONE);
	}


}

void EnemyBulletManager::clean()
{
	SDL_DestroyTexture(this->bulletTexture);
	delete soundPlayer;

}
#include "Player.h"

Player::Player(SDL_Renderer* sdlRenderer, int _windowWidth, int _windowHeight)
{
	renderer = sdlRenderer;
	windowWidth = _windowWidth;
	windowHeight = _windowHeight;
}

void Player::init()
{

	//SDL_Surface* image = IMG_Load("\\\\students.uce.ac.uk\\filespace\\mb20\\tic\\S20158721\\Git\\milestones-Landwere\\code\\cplusplus_programming_for_games\\assets\\chibiCarlo.png");
	SDL_Surface* image = IMG_Load("assets\\tankPlaceholder.png");
	if (image == nullptr)
	{
		std::cout << SDL_GetError() << std::endl;
		return;
	}

	texture = SDL_CreateTextureFromSurface(renderer, image);

	portion.x = (float)windowWidth / 2;
	portion.y = (float)windowHeight / 2;

	boundingSphere = new Sphere(portion.x + (portion.w / 2), portion.y + (portion.h / 2), portion.w / 2);
	cout << boundingSphere;


}

void Player::render()
{
	float playerWidth = 0.1f * (float)windowWidth;
	float playerHeight = 0.1f * (float)windowHeight;
	portion.w = (int)playerWidth;
	portion.h = (int)playerHeight;

	SDL_Point center = { portion.w / 2, portion.h / 2 };

	
	//SDL_RenderCopy(renderer, texture, NULL, &portion);
	SDL_RenderCopyEx(renderer, texture, 0, &portion, rotation, &center, SDL_FLIP_NONE);
}

void Player::setXY(int x, int y)
{
	portion.x = x;
	portion.y = y;
	boundingSphere->x = portion.x;
	boundingSphere->y = portion.y;
}
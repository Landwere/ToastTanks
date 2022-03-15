#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include <string>
#include <iostream>
#include <fstream>
#include "Player.h"
using namespace std;
class TiledMap
{
public:
	TiledMap(SDL_Renderer* sdlRenderer, std::string tiledMapFilename);

	int init();
	void clean();
	void render(SDL_Rect PlayerPortion, Player* player, int& score);
	void loadMap(string file);
private:
	const int sourceTileSizePx = 16;
	const int tileWidth = 100;
	const int tileHeight = 100;

	std::string filename;
	SDL_Renderer* renderer;
	SDL_Texture* texture;
	int newTileMap[6][8];
	Player* player;
	SDL_Rect playerRect;
	bool animFrame = true;
	bool playerOnMap;

	//time between shots
	const int ANIM_TIMER_MS = 1000;

	unsigned int lastFrame = 0;
};


const int mapWidth = 8;
const int mapHeight = 6;


/*
const int map[mapHeight][mapHeight] =
{
	{42,49,50,50,50,50,50,51},
	{42,49,50,50,50,50,50,51},
	{42,49,50,50,50,50,50,51},
	{42,49,50,50,50,50,40,63},
	{42,61,41,50,50,40,63,42},
	{65,42,61,62,62,63,42,64}
};*/


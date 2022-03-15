#pragma once
#include <iostream>
#define SDL_MAIN_HANDLED
#include <SDL.h>
#include <SDL_image.h>
#include "Player.h"
#include "FontRenderer.h"
#include "TiledMap.h"
#include "BulletManager.h"
#include "Sprite.h"
#include "enemyTurret.h"
#include "MainMenu.h"
#include "EnemyBulletManager.h"

const int screenWidth = 800;
const int screenHeight = 600;

class GameLoop
{

public:
	int init();

	void update();
	void render();

	bool keepalive();
	void handleInput(SDL_Scancode& keyScanCode);

	void clean();
	void cleanForRestart();

	bool gamerunning = false;
	bool gameOver = false;
	int gameWin = false;


	int level = 0;
private:

	Sprite* flag;
	Sprite* flag2;
	Sprite* burst;
	Sprite* coin;

	Sphere* playerBoundingSphere;

	int score;
	MainMenu* menu;
	enemyTurret* turret; 
	enemyTurret* turret1; 
	enemyTurret* turret2;

	SDL_Window *window;
	SDL_Surface *screenSurface;
	SDL_Renderer* renderer = nullptr;
	std::unique_ptr<FontRenderer> fontRenderer;
	
	EnemyBulletManager* bulletman;
	EnemyBulletManager* bulletman1;
	EnemyBulletManager* bulletman2;
	std::unique_ptr<TiledMap> tiledMap;
	SoundPlayer* soundPlayer;
	Player* player = nullptr;
	BulletManager* bulletM;
};


#include "GameLoop.h"

#include "SoundPlayer.h"



int GameLoop::init()
{


	if (SDL_Init(SDL_INIT_VIDEO) < 0)
	{
		std::cout << "could not initilize the SDL2!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}
	window = SDL_CreateWindow
	(
		"GAME window :D",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, screenWidth, screenHeight, SDL_WINDOW_SHOWN
	);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (window == NULL)
	{
		std::cout << "Could not initilize window!" << std::endl;
		std::cout << SDL_GetError() << std::endl;
		return -1;
	}

	screenSurface = SDL_GetWindowSurface(window);
	SDL_FillRect(screenSurface, NULL, SDL_MapRGB(screenSurface->format, 0, 70, 80));
	SDL_UpdateWindowSurface(window);

	player = new Player(renderer, SDL_GetWindowSurface(window)->w, SDL_GetWindowSurface(window)->h);
	player->init();

	//player = new Player(renderer, 60, 90);
	//std::cout << SDL_GetWindowSurface(window)->w << std::endl;

	fontRenderer = std::unique_ptr<FontRenderer>(new FontRenderer(renderer));
	fontRenderer->init();

	bulletM = new BulletManager(this->renderer, this->player);
	bulletM->init();

	tiledMap = std::unique_ptr<TiledMap>(new TiledMap(renderer, "assets/tilemapFire.png"));
	tiledMap->init();
	

	flag = new Sprite("assets\\flag.png", this->renderer);
	flag->SetPosition(300, 100);

	flag2 = new Sprite("assets\\flag.png", this->renderer);
	flag2->SetPosition(100, 400);
	flag2->SetVisible(false);

	coin = new Sprite("assets\\pickup.png", this->renderer);
	coin->SetPosition(400, 100);

	turret1 = new enemyTurret("assets\\enemyTurret.png", this->renderer);
	turret1->SetPosition(200, 500);

	turret = new enemyTurret("assets\\enemyTurret.png", this->renderer);
	turret->SetPosition(200,100);
	turret->SetVisible(false);

	turret1->SetVisible(false);
	turret2 = new enemyTurret("assets\\enemyTurret.png", this->renderer);
	turret2->SetPosition(500, 200);
	turret2->SetVisible(false);

	bulletman = new EnemyBulletManager(this->renderer, this->turret);
	bulletman->init();

	bulletman1 = new EnemyBulletManager(this->renderer, this->turret1);
	bulletman1->init();

	bulletman2 = new EnemyBulletManager(this->renderer, this->turret2);
	bulletman2->init();
	//burst = new Sprite("assets\\Toast.png", this->renderer);

	menu = new MainMenu(this->renderer, this->screenSurface, SDL_GetWindowSurface(window)->w, SDL_GetWindowSurface(window)->h, this->window);

	soundPlayer = new SoundPlayer();
	soundPlayer->init();

	soundPlayer->PlaySound(3, true);

	return 0;
}

void GameLoop::update()
{
	if (player->SphereCollision(*flag))
	{
		if (level == 0)
		{
			
			cout << "Collide" << std::endl;
			tiledMap->loadMap("assets/Level2Map.txt");
			//flag->SetVisible(false);
			turret->SetVisible(true);
			turret1->SetVisible(true);
			turret2->SetVisible(true);
			flag->SetVisible(false);
			flag2->SetVisible(true);
			coin->SetVisible(true);
			turret->SetPosition(400, 200);
			player->setXY(400, 500);
			level = 1;
			return;
		}
	
	}
	if (player->SphereCollision(*flag2))
	{
		//only collide if object enabled
		if (flag2->visible)
		{
			gameWin = true;
		}
		
	}
	if (player->SphereCollision(*coin))
	{
		//only collide if object enabled
		if (coin->visible == true)
		{
			cout << "Collide" << std::endl;
			++score;
		}
		coin->SetVisible(false);
	}
	if (bulletM->SphereCollision(*turret))
	{
		//only collide if object enabled
		if (turret->visible)
		{
			turret->SetVisible(false);
			score += 2;
		}
	}
	if (bulletM->SphereCollision(*turret1))
	{
		//only collide if object enabled
		if (turret1->visible)
		{
			turret1->SetVisible(false);
			score += 2;
		}
	}
	if (bulletM->SphereCollision(*turret2))
	{
		//only collide if object enabled
		if (turret2->visible)
		{
			turret2->SetVisible(false);
			score += 2;
		}
	}
	playerBoundingSphere = player->boundingSphere;

	if (bulletman->SphereCollision(*player) || bulletman1->SphereCollision(*player) || bulletman2->SphereCollision(*player))
	{
		gameOver = true;
	}
	turret->moveTowardsPlayer(player->getYPos(), player->getXPos(), player->getAngle());
	turret1->moveTowardsPlayer(player->getYPos(), player->getXPos(), player->getAngle());
	turret2->moveTowardsPlayer(player->getYPos(), player->getXPos(), player->getAngle());
	bulletM->update();
	if (turret->visible)
	{
		bulletman->proccessInput();
	}
	if (turret1->visible)
	{
		bulletman1->proccessInput();
	}
	if (turret2->visible)
	{
		bulletman2->proccessInput();
	}
	bulletman->update();
	bulletman1->update();
	bulletman2->update();
	
}

void GameLoop::render()
{
	//ran when the final level is completed
	if (gameWin)
	{

		//SDL_Texture* texTarget = SDL_CreateTexture(renderer, skyblue, SDL_TEXTUREACCESS_TARGET, 100, 100);
		SDL_SetRenderDrawColor(renderer, 163, 203, 56, 1.0);
		//SDL_SetRenderTarget(renderer, texTarget);
		SDL_RenderClear(renderer);
		menu->render();


		//SDL_RenderCopyEx(renderer, texTarget, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);
		fontRenderer->render("You Win!", 400, 200, SDL_GetWindowSurface(window)->w / 2 - 200, SDL_GetWindowSurface(window)->h / 2 - 300);
		fontRenderer->render("Click To Return to Menu", 300, 150, SDL_GetWindowSurface(window)->w / 2 - 150, SDL_GetWindowSurface(window)->h / 2 - 100);
		fontRenderer->render("Press Esc to quit", 300, 150, SDL_GetWindowSurface(window)->w / 2 - 150, SDL_GetWindowSurface(window)->h / 2 + 100);
		SDL_RenderPresent(renderer);

	}
	//ran if the player dies
	else if (gameOver)
	{

	//SDL_Texture* texTarget = SDL_CreateTexture(renderer, skyblue, SDL_TEXTUREACCESS_TARGET, 100, 100);
	SDL_SetRenderDrawColor(renderer, 234, 32, 39, 1.0);
	//SDL_SetRenderTarget(renderer, texTarget);
	SDL_RenderClear(renderer);
	menu->render();


	//SDL_RenderCopyEx(renderer, texTarget, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);
	fontRenderer->render("GAME OVER!", 400, 200, SDL_GetWindowSurface(window)->w / 2 - 200, SDL_GetWindowSurface(window)->h / 2 - 300);
	fontRenderer->render("Click To Return to Menu", 300, 150, SDL_GetWindowSurface(window)->w / 2 - 150, SDL_GetWindowSurface(window)->h / 2 - 100);
	fontRenderer->render("Press Esc to quit", 300, 150, SDL_GetWindowSurface(window)->w / 2 - 150, SDL_GetWindowSurface(window)->h / 2 + 100);
	SDL_RenderPresent(renderer);

	}
	//render objects if game is running 
	else if (gamerunning)
	{
		SDL_RenderClear(renderer);
		tiledMap->render(player->portion, player, score);
		flag->Render();
		flag2->Render();
		coin->Render();
	
		bulletman->draw();
		bulletman1->draw();
		bulletman2->draw();
		turret->Render();
		turret1->Render();
		turret2->Render();
		bulletM->draw();
		
		player->render();
		fontRenderer->render("Score: " + std::to_string(score), 100, 50, 0, 0);
		SDL_RenderPresent(renderer);
	}
	else
	{
		//SDL_UpdateWindowSurface(window);
		Uint32 	skyblue = SDL_MapRGB(screenSurface->format, 25, 42, 86);

		//SDL_Texture* texTarget = SDL_CreateTexture(renderer, skyblue, SDL_TEXTUREACCESS_TARGET, 100, 100);
		SDL_SetRenderDrawColor(renderer, 6, 82, 221, 1.0);
		//SDL_SetRenderTarget(renderer, texTarget);
		SDL_RenderClear(renderer);
		menu->render();
	

		//SDL_RenderCopyEx(renderer, texTarget, NULL, NULL, 0, NULL, SDL_FLIP_VERTICAL);
		fontRenderer->render("Click To Play Game", 300, 150, SDL_GetWindowSurface(window)->w / 2 - 150, SDL_GetWindowSurface(window)->h / 2 - 100);
		fontRenderer->render("Press Esc to quit", 300, 150, SDL_GetWindowSurface(window)->w / 2 -150, SDL_GetWindowSurface(window)->h / 2 + 100);
		SDL_RenderPresent(renderer);

	}




	//SDL_UpdateWindowSurface(window);

	

}

void GameLoop::clean()
{
	fontRenderer->clean();
	tiledMap->clean();
	bulletM->clean();
	bulletman->clean();
	bulletman1->clean();
	bulletman2->clean();
	delete soundPlayer;
	delete player;
	delete flag;
	delete coin;
	delete turret;
	delete turret1;
	delete turret2;
	SDL_DestroyWindow(window);
	SDL_Quit();
}

//reset all object to their starting positions and states
void GameLoop::cleanForRestart()
{
	tiledMap->loadMap("assets/Level1Map.txt");
	player->setXY(SDL_GetWindowSurface(window)->w / 2, SDL_GetWindowSurface(window)->h / 2);
	flag->SetPosition(300, 100);
	flag->SetVisible(true);	

	flag2->SetPosition(100, 400);
	flag2->SetVisible(false);
	
	coin->SetPosition(400, 100);
	
	coin->SetVisible(true);

	
	turret->SetPosition(200, 100);
	turret->SetVisible(false);
	turret1->SetPosition(200, 500);
	turret1->SetVisible(false);
	turret2->SetPosition(500, 200);
	turret2->SetVisible(false);



}


void GameLoop::handleInput(SDL_Scancode& keyScanCode)
{

	switch (keyScanCode)
	{
	case SDL_SCANCODE_D:
		player->moveRight();
		break;
	case SDL_SCANCODE_RIGHT:
		player->moveRight();
		break;

	case SDL_SCANCODE_A:
		player->moveLeft();
		break;
	case SDL_SCANCODE_LEFT:
		player->moveLeft();
		break;

	case SDL_SCANCODE_W:
		player->moveUp();
		break;
	case SDL_SCANCODE_UP:
		player->moveUp();
		break;

	case SDL_SCANCODE_S:
		player->moveDown();
		break;
	case SDL_SCANCODE_DOWN:
		player->moveDown();
		break;

	case SDL_SCANCODE_SPACE:
		bulletM->proccessInput();
		break;
	case SDL_SCANCODE_ESCAPE:
		clean();
		break;
	}
	

}


bool GameLoop::keepalive()
{
	SDL_Event userInput;
	while (SDL_PollEvent(&userInput))
	{
		if (userInput.type == SDL_QUIT)
		{
			return false;
		}

		if (userInput.type == SDL_KEYDOWN)
		{
			handleInput(userInput.key.keysym.scancode);
		}
		if (userInput.type == SDL_MOUSEBUTTONDOWN)
		{
			if (!gamerunning)
			{
				turret->SetVisible(true);
				}
				std::cout << gameWin;
				gamerunning = true;
				
				if (gameOver || gameWin)
				{
					
					gameOver = false;
					gameWin = false;
					gamerunning = false;
					score = 0;
					level = 0;
					cleanForRestart();
				}
			
				
		}
	}

	return true;
}
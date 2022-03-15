#include "TiledMap.h"

TiledMap::TiledMap(SDL_Renderer* sdlRenderer, std::string tiledMapFilename) {
	filename = tiledMapFilename;
	renderer = sdlRenderer;
}

int TiledMap::init()
{
	SDL_Surface* image = IMG_Load(filename.c_str());
	texture = SDL_CreateTextureFromSurface(renderer, image);
	SDL_FreeSurface(image);
	loadMap("assets/Level1Map.txt");

	return 0;
}

void TiledMap::render(SDL_Rect PlayerPortion, Player* player, int& score)
{
	playerOnMap = false;
	playerRect = PlayerPortion;

	SDL_Rect result;
	for (int i = 0; i < mapHeight; i++)
	{
		for (int j = 0; j < mapWidth; j++)
		{
			if (newTileMap[i][j] == 65 || newTileMap[i][j] == 71)
			{
				if (animFrame)
				{
					newTileMap[i][j] = 71;
				}
				else
				{
					newTileMap[i][j] = 65;
				}
			}
			if (newTileMap[i][j] == 64 || newTileMap[i][j] == 70)
			{
				if (animFrame)
				{
					newTileMap[i][j] = 70;
				}
				else
				{
					newTileMap[i][j] = 64;
				}
			}
			if (newTileMap[i][j] == 48 || newTileMap[i][j] == 54)
			{
				if (animFrame)
				{
					newTileMap[i][j] = 54;
				}
				else
				{
					newTileMap[i][j] = 48;
				}
			}
			if (newTileMap[i][j] == 60 || newTileMap[i][j] == 66)
			{
				if (animFrame)
				{
					newTileMap[i][j] = 66;
				}
				else
				{
					newTileMap[i][j] = 60;
				}
			}
			//single tree fire anim
			if (newTileMap[i][j] == 78 || newTileMap[i][j] == 102)
			{
				if (animFrame)
				{
					newTileMap[i][j] = 102;
				}
				else
				{
					newTileMap[i][j] = 78;
				}
			}
			//Double tree fire anim
			if (newTileMap[i][j] == 90 || newTileMap[i][j] == 114)
			{
				if (animFrame)
				{
					newTileMap[i][j] = 114;
				}
				else
				{
					newTileMap[i][j] = 90;
				}
			}

			SDL_Rect sourceRect;
			sourceRect.x = (newTileMap[i][j] % 12) * sourceTileSizePx;
			sourceRect.y = (newTileMap[i][j] / 12) * sourceTileSizePx;
			sourceRect.h = sourceTileSizePx;
			sourceRect.h = sourceTileSizePx;
			sourceRect.w = sourceTileSizePx;

			SDL_Rect renderRect;
			renderRect.x = j * tileWidth;
			renderRect.y = i * tileHeight;
			renderRect.h = tileHeight;
			renderRect.w = tileWidth;

			if (SDL_IntersectRect(&renderRect, &playerRect,  &result ))
			{
				playerOnMap = true;
				if (newTileMap[i][j] == 42)
				{
					//player->setXY(player->lastX, player->lastY);
					//player->portion.x = player->lastX;
					//player->portion.y = player->lastY;
					player->setXY(400, 500);
					/*if (player->IsmoveUp == true)
					{
						player->moveDown();
					}
					else
					{
						player->moveUp();
					}*/
				}
				//single tree fire
				else if (newTileMap[i][j] == 48 || newTileMap[i][j] == 54)
				{
					score--;
					newTileMap[i][j] = 78;
				}
				//double tree fire
				else if (newTileMap[i][j] == 60 || newTileMap[i][j] == 66)
				{
					score--;
					newTileMap[i][j] = 90;
				}
			}


			if (SDL_GetTicks() - lastFrame > ANIM_TIMER_MS)
			{
				if (animFrame)
				{
					animFrame = false;
				}
				else
				{
					animFrame = true;
				}
				lastFrame = SDL_GetTicks();
			}
		
			SDL_RenderCopy(renderer, texture, &sourceRect, &renderRect);
		}
	}
	if (!playerOnMap)
	{
		player->setXY(400, 500);
	}
}

void TiledMap::loadMap(string file)
{
	ifstream mapFile;
	mapFile.open(file.c_str());
	
	for (int i = 0; i < 6; i++)
	{
		std::string line;
		getline(mapFile, line);
		
		for (int j = 0; j < 8; j++) {
		    auto space = line.find(' ');
			string tileId = line.substr(0, space);
			int tile = std::stoi(tileId);
			line.erase(0, space + 1);
			newTileMap[i][j] = tile;
		}
	}
}
void TiledMap::clean()
{

}
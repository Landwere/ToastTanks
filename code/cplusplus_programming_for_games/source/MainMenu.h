#pragma once
#include <SDL.h>
#include <iostream>
#include <SDL_image.h>
#include "FontRenderer.h"

class MainMenu
{
public:
	MainMenu(SDL_Renderer* sdlRenderer, SDL_Surface* screenSurface, int _windowWidth, int _windowHeight, SDL_Window* SDLwindow)
	{
		window = SDLwindow;
		Surface = screenSurface;
		Renderer = sdlRenderer;
		skyblue = SDL_MapRGB(Surface->format, 65, 193, 193);
		playbutton.w = 200;
		playbutton.h = 50;
		playbutton.y = 400;
		playbutton.x = 600;
		playText = new FontRenderer(sdlRenderer);
		playText->init();
		SDL_Surface* image = IMG_Load("assets\\PlayButton.png");
		texture = SDL_CreateTextureFromSurface(sdlRenderer, image);
		playPortion.x = (float)_windowWidth / 2;
		playPortion.y = 100;
		playPortion.w = 200;
		playPortion.h = 100;
	};

	bool proccessInput()
	{
		int x, y;
		SDL_GetMouseState(&x, &y);

		std::cout << y  << std::endl;
		std::cout << playPortion.y << std::endl;
		std::cout << playPortion.y - y;
		//if (y - playPortion.y < playPortion.h && x - playPortion.x < playPortion.w && y  - playPortion.y > -playPortion.h && x - playPortion.x > -playPortion.w)
		//if (y - playPortion.y > -1)
		//{
			
			return true;
			//std::cout << "HEllo %d, %d", x, y;
		//}
		return false;
		
	}
	void render()
	{

		//SDL_FillRect(Surface, NULL, skyblue);
		//SDL_RenderCopy(Renderer, texture, NULL, &playPortion);
		//SDL_FillRect(Surface, &playbutton, (0, 1, 255));
		//playText->render("Play Game", 100, 50, 1, 1);
	}
private:
	SDL_Renderer* Renderer;
	SDL_Surface* Surface;
	Uint32 skyblue;
	SDL_Rect playbutton;
	FontRenderer* playText;
	SDL_Window* window;
	SDL_Rect playPortion;

	SDL_Texture* texture = nullptr;

};


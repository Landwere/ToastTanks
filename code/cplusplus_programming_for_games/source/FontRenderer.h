#pragma once
#include <SDL_ttf.h>
#include <SDL.h>
#include <string>
#include <iostream>

class FontRenderer
{

public:
	FontRenderer(SDL_Renderer* sdlRenderer);
	void init();
	void render(std::string text, int width, int height, int x, int y);
	void clean();

private:
	SDL_Rect portion;

	SDL_Renderer* renderer;
	TTF_Font* font;
};


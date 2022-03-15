#include "FontRenderer.h"

FontRenderer::FontRenderer(SDL_Renderer* sdlRenderer)
{
	renderer = sdlRenderer;
}

void FontRenderer::init()
{
	int init = TTF_Init();
	if (init != 0)
	{
		std::cout << SDL_GetError() << std::endl;
	}
	font = TTF_OpenFont("assets/OpenSans-Regular.ttf", 14);
	if (font == NULL)
	{
		std::cout << SDL_GetError() << std::endl;
	}
}



void FontRenderer::clean()
{
	//free up all the recources we used to render 
	TTF_CloseFont(font);
}

void FontRenderer::render(std::string text, int width, int height, int x, int y)
{
	SDL_Color colour = SDL_Color();
	colour.r = 0;
	colour.g = 0;
	colour.b = 0;
	colour.a = 255;


	portion.w = width;
	portion.h = height;
	portion.x = x;
	portion.y = y;
	//creates an image representing the text inputtted
	SDL_Surface* textImage = TTF_RenderText_Solid(font, text.c_str(), colour);
	//once the image is created, we can render it the same as the player
	SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, textImage);
	SDL_RenderCopy(renderer, texture, NULL, &portion);

	SDL_DestroyTexture(texture);
	SDL_FreeSurface(textImage);
}
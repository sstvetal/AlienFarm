#pragma once
#include "SDL2/SDL.h"
#include "TextureLoader.h"
#include "Vector2D.h"
#include "Timer.h"
#include "MathAddon.h"


class Plant
{
public:
	Plant(SDL_Renderer* renderer, Vector2D setPos);
	void update(float dT);
	void draw(SDL_Renderer* renderer, int tileSize);
	Vector2D getPos();

private:
	void drawTexture(SDL_Renderer* renderer, SDL_Texture* textureSelected, int tileSize);

	Vector2D pos;
	float fDrawScale = 1.0f;
	Timer  timerGrowth, timerMoveUpAndDown;


	SDL_Texture* textureSmallMain = nullptr, * textureSmallShadow = nullptr,
		* textureMain = nullptr, * textureShadow = nullptr;

};
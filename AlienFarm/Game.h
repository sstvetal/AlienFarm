#pragma once
#include <chrono>
#include "SDL2/SDL.h"
#include "TextureLoader.h"
#include "Vector2D.h"
#include "Level.h"



class Game
{
public:
	Game(SDL_Window* window, SDL_Renderer* renderer, int windowWidth, int windowHeight);
	~Game();


private:
	void processEvents(bool& running);
	void update(float dT);
	void draw(SDL_Renderer* renderer);

	int mouseDownStatus = 0;

	const int tileSize = 64;
	Level level;
};
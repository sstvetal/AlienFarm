#pragma once
#include "SDL2/SDL.h"


class Tile
{
public:
	Tile();
	void draw(SDL_Renderer* renderer, int x, int y, int tileSize);
	void setTypeID(int setTypeID);

private:
	int typeID;

};
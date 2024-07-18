#pragma once
#include <vector>
#include "SDL2/SDL.h"
#include "Tile.h"

class Level
{
public:
	Level(SDL_Renderer* renderer, int setTileCountX, int setTileCountY);

	void draw(SDL_Renderer* renderer, int tileSize);
	void drawSahdows(SDL_Renderer* renderer, int tileSize);
	void setTileTypeIDSelected(int setTileTypeIDSelected);
	void placeTileTypeIDSelected(int x, int y);
	bool checkIfTileOkForPlant(int x, int y, bool growsOnWetDirt);


private:
	std::vector<Tile> listTiles;
	const int tileCountX, tileCountY;

	int tileTypeIDSelected = 0;
};
#include "Level.h"

Level::Level(SDL_Renderer* renderer, int setTileCountX, int setTileCountY):
	tileCountX(setTileCountX),tileCountY(setTileCountY)
{
	size_t listTilesSize = (size_t)tileCountX * tileCountY;
	listTiles.assign(listTilesSize, Tile(renderer));
}

void Level::draw(SDL_Renderer* renderer, int tileSize)
{
	for (int y = 0; y < tileCountY; y++)
	{
		for (int x = 0; x < tileCountX; x++)
		{
			int index = x + y * tileCountX;
			listTiles[index].draw(renderer, x, y, tileSize);
			listTiles[index].drawShadows(renderer, x, y, tileSize, listTiles, tileCountX, tileCountY);
		}

	}
}

void Level::drawSahdows(SDL_Renderer* renderer, int tileSize)
{
	for (int y = 0; y < tileCountY; y++)
	{
		for (int x = 0; x < tileCountX; x++)
		{
			int index = x + y * tileCountX;
			listTiles[index].drawShadows(renderer, x, y, tileSize,
    			 listTiles, tileCountX, tileCountY);
		}

	}
}

void Level::setTileTypeIDSelected(int setTileTypeIDSelected)
{
	tileTypeIDSelected = setTileTypeIDSelected;
}

void Level::placeTileTypeIDSelected(int x, int y)
{
	int index = x + y * tileCountX;
	if(index > -1 && index < listTiles.size() && 
	   x > -1 && x < tileCountX &&
	   y > -1 && y < tileCountY)
	{
		listTiles[index].setTypeID(tileTypeIDSelected);

		Tile::refreshSurrondingIsWet(x, y, listTiles, tileCountX, tileCountY);
	}
}

bool Level::checkIfTileOkForPlant(int x, int y, bool growsOnWetDirt)
{
	int index = x + y * tileCountX;
	if (index > -1 && index < listTiles.size() &&
		x > -1 && x < tileCountX &&
		y > -1 && y < tileCountY)
		return listTiles[index].checkIfOkForPlant(growsOnWetDirt);

	return false;
}

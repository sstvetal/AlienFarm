#include "Level.h"

Level::Level(int setTileCountX, int setTileCountY):
	tileCountX(setTileCountX),tileCountY(setTileCountY)
{
	size_t listTilesSize = (size_t)tileCountX * tileCountY;
	listTiles.assign(listTilesSize, Tile());
}

void Level::draw(SDL_Renderer* renderer, int tileSize)
{
	for (int y = 0; y < tileCountY; y++)
	{
		for (int x = 0; x < tileCountX; x++)
		{
			int index = x + y * tileCountX;
			listTiles[index].draw(renderer, x, y, tileSize);
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
	}
}

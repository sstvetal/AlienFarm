#include "Tile.h"

Tile::Tile() :
	typeID(2)
{
}

void Tile::draw(SDL_Renderer* renderer, int x, int y, int tileSize)
{
	bool dark = ((x + y) % 2 == 0);

	switch(typeID)
	{
		//water
	case 0:
		SDL_SetRenderDrawColor(renderer, 0, 67, 190, 255);
		break;

		//dirt
	case 1:
		if (dark)
		{
			SDL_SetRenderDrawColor(renderer, 80, 47, 30, 255);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 90, 56, 32, 255);
		}
		break;

		//sand
	case 2:
	default:
		if(dark)
		{
			SDL_SetRenderDrawColor(renderer, 100, 33, 60, 200);
		}
		else
		{
			SDL_SetRenderDrawColor(renderer, 100, 50, 60, 200);
		}
		break;
	}


	SDL_Rect rect = { x * tileSize, y * tileSize, tileSize, tileSize };
	SDL_RenderFillRect(renderer, &rect);	
}


void Tile::setTypeID(int setTypeID)
{
	if(setTypeID > -1 && setTypeID <= 2)
	{
		typeID = setTypeID;
	}
}

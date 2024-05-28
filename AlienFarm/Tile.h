#pragma once

#include <vector>
#include "SDL2/SDL.h"
#include "TextureLoader.h"


class Tile
{
private:
	struct Type
	{
		int height = 0;
		SDL_Color colorDark = {};
		SDL_Color colorLight = {};
	};



public:
	Tile(SDL_Renderer* renderer);
	void draw(SDL_Renderer* renderer, int x, int y, int tileSize);
	void drawShadows(SDL_Renderer* renderer, int x, int y, int tileSize,
		std::vector<Tile>& listTiles, int tileCountX, int tileCountY);

	void setTypeID(int setTypeID);

private:
	bool isTileHigher(int x, int y, std::vector<Tile>& listTiles, int tileCountX, int tileCountY);


	int typeID;


	static const std::vector<Type> listTileTypes;


	SDL_Texture* textureTileShadowTop = nullptr,
		* textureTileShadowRight = nullptr,
		* textureTileShadowBottom = nullptr,
		* textureTileShadowLeft = nullptr,


	    * textureTileShadowTopLeft = nullptr,
		* textureTileShadowTopRight = nullptr,
		* textureTileShadowBottomLeft = nullptr,
		* textureTileShadowBottomRight = nullptr;
};
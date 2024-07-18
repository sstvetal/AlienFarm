#pragma once

#include <vector>
#include "SDL2/SDL.h"
#include "TextureLoader.h"


class Tile
{
private:
	struct Type
	{
		std::string name = "";
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
	static void refreshSurrondingIsWet(int x, int y, std::vector<Tile>& listTiles, int tileCountX, int tileCountY);

	bool checkIfOkForPlant(bool growsOnWetDirt);

private:
	bool isTileHigher(int x, int y, std::vector<Tile>& listTiles, int tileCountX, int tileCountY);

	int typeID;
	bool isWet = false;


	static const std::vector<Type> listTileTypes;

	static std::vector<SDL_Texture*> listTextureTileShadows;
};
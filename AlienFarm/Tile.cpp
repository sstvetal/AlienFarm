#include "Tile.h"


const std::vector<Tile::Type> Tile::listTileTypes = {
	{ 0, SDL_Color{ 0, 60, 190 } , SDL_Color{ 0, 60, 190 } },           //water
	{ 1, SDL_Color{ 80, 47, 30 } , SDL_Color{ 90, 56, 32 } },           //dirt
	{ 2, SDL_Color{  100, 33, 60 } , SDL_Color{ 100, 50, 60 } },        //sand
	{ 2, SDL_Color{  11, 100, 100 } , SDL_Color{ 14, 131, 131 } },      //green
	{ 2, SDL_Color{  184, 176, 33 } , SDL_Color{ 218, 209, 50 } },      //yellow
	{ 2, SDL_Color{  33, 41, 184 } , SDL_Color{ 50, 59, 218, } },       //blue
	{ 2, SDL_Color{  167, 167, 167 } , SDL_Color{ 199, 199, 199 } }     //white
};


Tile::Tile(SDL_Renderer* renderer) :
	typeID(2)
{
	textureTileShadowTop = TextureLoader::loadTexture(renderer, "Tile Shadow Top.bmp");
	textureTileShadowRight = TextureLoader::loadTexture(renderer, "Tile Shadow Right.bmp");
	textureTileShadowBottom = TextureLoader::loadTexture(renderer, "Tile Shadow Bottom.bmp");
	textureTileShadowLeft = TextureLoader::loadTexture(renderer, "Tile Shadow Left.bmp");


	textureTileShadowTopLeft = TextureLoader::loadTexture(renderer, "Tile Shadow Top Left.bmp");
	textureTileShadowTopRight = TextureLoader::loadTexture(renderer, "Tile Shadow Top Right.bmp");
	textureTileShadowBottomLeft = TextureLoader::loadTexture(renderer, "Tile Shadow Bottom Left.bmp");
	textureTileShadowBottomRight = TextureLoader::loadTexture(renderer, "Tile Shadow Bottom Right.bmp");
}

void Tile::draw(SDL_Renderer* renderer, int x, int y, int tileSize)
{
	if(typeID > -1 && typeID < listTileTypes.size())
	{
		const Type& typeSelected = listTileTypes[typeID];
		bool dark = ((x + y) % 2 == 0);

		SDL_Color colorTile = (dark ? typeSelected.colorDark : typeSelected.colorLight);
		SDL_SetRenderDrawColor(renderer, colorTile.r, colorTile.g, colorTile.b, 255);

		SDL_Rect rect = { x * tileSize, y * tileSize, tileSize, tileSize };
		SDL_RenderFillRect(renderer, &rect);	
	}

}

void Tile::drawShadows(SDL_Renderer* renderer, int x, int y, int tileSize, 
	std::vector<Tile>& listTiles, int tileCountX, int tileCountY)
{
	SDL_Rect rect = { x * tileSize, y * tileSize, tileSize, tileSize };

	if (isTileHigher(x, y - 1, listTiles, tileCountX, tileCountY) && textureTileShadowTop != nullptr)
		SDL_RenderCopy(renderer, textureTileShadowTop, NULL, &rect);

	if (isTileHigher(x + 1, y, listTiles, tileCountX, tileCountY) && textureTileShadowRight != nullptr)
		SDL_RenderCopy(renderer, textureTileShadowRight, NULL, &rect);

	if (isTileHigher(x, y + 1, listTiles, tileCountX, tileCountY) && textureTileShadowBottom != nullptr)
		SDL_RenderCopy(renderer, textureTileShadowBottom, NULL, &rect);

	if (isTileHigher(x - 1, y, listTiles, tileCountX, tileCountY) && textureTileShadowLeft != nullptr)
		SDL_RenderCopy(renderer, textureTileShadowLeft, NULL, &rect);


	if (isTileHigher(x - 1 , y - 1 , listTiles, tileCountX, tileCountY) &&
	   isTileHigher(x - 1 , y , listTiles, tileCountX, tileCountY) == false &&
	   isTileHigher(x , y - 1 , listTiles, tileCountX, tileCountY) == false &&
	   textureTileShadowTopLeft !=nullptr)
	   SDL_RenderCopy(renderer, textureTileShadowTopLeft, NULL, &rect);


	if (isTileHigher(x + 1 , y - 1 , listTiles, tileCountX, tileCountY) &&
		isTileHigher(x + 1 , y , listTiles, tileCountX, tileCountY) == false &&
		isTileHigher(x , y - 1 , listTiles, tileCountX, tileCountY) == false &&
		textureTileShadowTopRight !=nullptr)
		SDL_RenderCopy(renderer, textureTileShadowTopRight, NULL, &rect);


	if (isTileHigher(x - 1 , y + 1 , listTiles, tileCountX, tileCountY) &&
		isTileHigher(x - 1 , y , listTiles, tileCountX, tileCountY) == false &&
		isTileHigher(x , y + 1 , listTiles, tileCountX, tileCountY) == false &&
		textureTileShadowBottomLeft !=nullptr)
		SDL_RenderCopy(renderer, textureTileShadowBottomLeft, NULL, &rect);


	if (isTileHigher(x + 1 , y + 1 , listTiles, tileCountX, tileCountY) &&
		isTileHigher(x + 1 , y , listTiles, tileCountX, tileCountY) == false &&
		isTileHigher(x , y + 1 , listTiles, tileCountX, tileCountY) == false &&
		textureTileShadowBottomRight !=nullptr)
		SDL_RenderCopy(renderer, textureTileShadowBottomRight, NULL, &rect);
}


void Tile::setTypeID(int setTypeID)
{
	if(setTypeID > -1 && setTypeID < listTileTypes.size())
	{
		typeID = setTypeID;
	}
}



bool Tile::isTileHigher(int x, int y, 
	std::vector<Tile>& listTiles, int tileCountX, int tileCountY)
{
	if(typeID > -1 && typeID < listTileTypes.size())
	{
		int indexOther = x + y * tileCountX;
		if(indexOther > -1 && indexOther < listTiles.size() && 
		   x > -1 && x < tileCountX &&
		   y > -1 && y < tileCountY)
		{
			int typeIDOther = listTiles[indexOther].typeID;

			if(typeIDOther > -1 && typeIDOther < listTileTypes.size())
			{
				return listTileTypes[typeIDOther].height > listTileTypes[typeID].height;
			}
		}
	}

	return false;
}

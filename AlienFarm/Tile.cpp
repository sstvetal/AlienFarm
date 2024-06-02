#include "Tile.h"


const std::vector<Tile::Type> Tile::listTileTypes = {
	{ "water", 0, SDL_Color{ 0, 60, 190 } , SDL_Color{ 0, 60, 190 } },               //water
	{ "dirt", 1, SDL_Color{ 80, 47, 30 } , SDL_Color{ 90, 56, 32 } },                //dirt
	{ "sand",2, SDL_Color{  100, 33, 60 } , SDL_Color{ 100, 50, 60 } },              //sand
	{ "grassGreen",2, SDL_Color{  11, 100, 100 } , SDL_Color{ 14, 131, 131 } },      //green
	{ "grassYellow",2, SDL_Color{  184, 176, 33 } , SDL_Color{ 218, 209, 50 } },     //yellow
	{ "grassBlue",2, SDL_Color{  33, 41, 184 } , SDL_Color{ 50, 59, 218, } },        //blue
	{ "grassWhite",2, SDL_Color{  167, 167, 167 } , SDL_Color{ 199, 199, 199 } }     //white
};

std::vector<SDL_Texture*> Tile::listTextureTileShadows;


Tile::Tile(SDL_Renderer* renderer) :
	typeID(2)
{
	if(listTextureTileShadows.empty())
	{
		std::vector<std::string> listTileShadowNames{ "Top Left", "Top", "Top Right", "Left",
			"Right", "Bottom Left", "Bottom", "Bottom Right"};

		for(const auto& nameSelected : listTileShadowNames)
		{
			listTextureTileShadows.push_back(TextureLoader::loadTexture(renderer, 
			    "Tile Shadow " + nameSelected + ".bmp"));
		}
	}
}

void Tile::draw(SDL_Renderer* renderer, int x, int y, int tileSize)
{
	if(typeID > -1 && typeID < listTileTypes.size())
	{
		const Type& typeSelected = listTileTypes[typeID];
		bool dark = ((x + y) % 2 == 0);

		SDL_Color colorTile = (dark ? typeSelected.colorDark : typeSelected.colorLight);
		if(typeSelected.name == "dirt" && isWet)
		{
			const float fWet = 0.65f;
			colorTile.r = (Uint8)(colorTile.r * fWet);
			colorTile.g = (Uint8)(colorTile.g * fWet);
			colorTile.b = (Uint8)(colorTile.b * fWet);
		}
		SDL_SetRenderDrawColor(renderer, colorTile.r, colorTile.g, colorTile.b, 255);

		SDL_Rect rect = { x * tileSize, y * tileSize, tileSize, tileSize };
		SDL_RenderFillRect(renderer, &rect);	
	}

}

void Tile::drawShadows(SDL_Renderer* renderer, int x, int y, int tileSize, 
	std::vector<Tile>& listTiles, int tileCountX, int tileCountY)
{
	SDL_Rect rect = { x * tileSize, y * tileSize, tileSize, tileSize };


	//Loop through the list and draw each shadow image
	for(int count = 0; count < listTextureTileShadows.size(); count++){
		SDL_Texture* textureSelected = listTextureTileShadows[count];

		if(textureSelected != nullptr){
			int index = count;
		    if(count >= 4)
		     	index++;

		    int xOff = index % 3 - 1;
		    int yOff = index / 3 - 1;

			bool isCorner = (abs(xOff) == 1 && abs(yOff) == 1);
			if(isCorner){
				if(isTileHigher( x + xOff, y + yOff, listTiles, tileCountX, tileCountY) &&
				   isTileHigher( x + xOff, y, listTiles, tileCountX, tileCountY) == false &&
				   isTileHigher( x, y + yOff, listTiles, tileCountX, tileCountY) == false)
				   SDL_RenderCopy(renderer, textureSelected, NULL, &rect);
			}
			else{
				if (isTileHigher(x + xOff, y + yOff, listTiles, tileCountX, tileCountY))
					SDL_RenderCopy(renderer, textureSelected, NULL, &rect);
			}
		}

	}	
}


void Tile::setTypeID(int setTypeID)
{
	if(setTypeID > -1 && setTypeID < listTileTypes.size())
	{
		typeID = setTypeID;
	}
}

void Tile::refreshSurrondingIsWet(int x, int y, std::vector<Tile>& listTiles, int tileCountX, int tileCountY)
{
	const int distance = 2;

	for(int x2 = x - distance; x2 <= x + distance; x2++)
	{
		for (int y2 = y - distance; y2 <= y + distance; y2++)
		{
			int index2 = x2 + y2 * tileCountX;
			if (index2 > -1 && index2 < listTiles.size() &&
				x2 > -1 && x2 < tileCountX &&
				y2 > -1 && y2 < tileCountY) {
			
			
				bool foundWater = false;

				for(int x3 = x2 - distance; x3 <= x2 + distance && foundWater == false; x3++)
				{
					for (int y3 = y2 - distance; y3 <= y2 + distance && foundWater == false; y3++)
					{
						int index3 = x3 + y3 * tileCountX;
						if (index3 > -1 && index3 < listTiles.size() &&
							x3 > -1 && x3 < tileCountX &&
							y3 > -1 && y3 < tileCountY)
						{
							int typeIDSelected = listTiles[index3].typeID;
							if(typeIDSelected > -1 && typeIDSelected < listTileTypes.size() &&
							   listTileTypes[typeIDSelected].name == "water")
							{
								foundWater = true;
							}


						}

					}
				}

				listTiles[index2].isWet = foundWater;

			}
			   
		}
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

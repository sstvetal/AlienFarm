#include "Plant.h"


const std::vector<Plant::Type> Plant::listPlantTypes =
{
	{"Plant 1", 1},
	{"Plant 2", 1},
	{"Plant 3", 1},
	{"Plant 4", 2},
	{"Plant 5", 2},
};



Plant::Plant(SDL_Renderer* renderer, int setTypeID, Vector2D setPos) :
	typeID(setTypeID), pos(setPos), timerGrowth(7.5f + MathAddon::randFloat() * 7.5f), timerMoveUpAndDown(2.0f, MathAddon::randFloat() * 2.0f)
{
	if(setTypeID > -1 && setTypeID < listPlantTypes.size())
	{
		std::string name = listPlantTypes[setTypeID].name;
		textureSmallMain = TextureLoader::loadTexture(renderer, name + " Small.bmp");
		textureSmallShadow = TextureLoader::loadTexture(renderer, name +" Small Shadow.bmp");
		textureMain = TextureLoader::loadTexture(renderer, name + ".bmp");
		textureShadow = TextureLoader::loadTexture(renderer, name +" Shadow.bmp");

		pos += computeOffset();
	}
}


void Plant::update(float dT)
{
	timerGrowth.countUp(dT);

	timerMoveUpAndDown.countUp(dT);
	if(timerMoveUpAndDown.timeSIsMax())
	{
		timerMoveUpAndDown.resetToZero();
	}

	float fDrawScaleMin = 0.95f;
	float fCos = (cos(timerMoveUpAndDown.computeFTime() * 2.0f * MathAddon::PI) + 1.0f) / 2.0f;
	fDrawScale = fDrawScaleMin + (1.0f - fDrawScaleMin) * fCos;

}

void Plant::draw(SDL_Renderer* renderer, int tileSize)
{
	if(timerGrowth.timeSIsMax())
	{
		drawTexture(renderer, textureShadow, tileSize);
		drawTexture(renderer, textureMain, tileSize);
	}
	else
	{
		drawTexture(renderer, textureSmallShadow, tileSize);
		drawTexture(renderer, textureSmallMain, tileSize);
	}

}

bool Plant::checkOverlapWithPlantTypeID(int x, int y, int plantTypeID)
{
	if(plantTypeID > -1 && plantTypeID < listPlantTypes.size())
	{
		return checkOverlap(x, y, listPlantTypes[plantTypeID].size);
	}
	return false;
}

bool Plant::checkOverlapWithMouse(int x, int y)
{
	return checkOverlap(x, y, 1);
}

void Plant::drawTexture(SDL_Renderer* renderer, SDL_Texture* textureSelected, int tileSize)
{
	if(renderer != nullptr && textureSelected != nullptr)
	{
		int w, h;
		SDL_QueryTexture(textureSelected, NULL, NULL, &w, &h);

		w = (int)round(w * fDrawScale);
		h = (int)round(h * fDrawScale);

		SDL_Rect rect = { (int)round(pos.x * tileSize) - w / 2,(int)round(pos.y * tileSize) - h / 2, w, h };
		SDL_RenderCopy(renderer, textureSelected, NULL, &rect);
	}
}

bool Plant::checkOverlap(int x, int y, int size)
{
	if(typeID > -1 && typeID < listPlantTypes.size())
	{
		float offset1 = computeOffset();

		int rect1Left = (int)(pos.x - offset1);
		int rect1Top = (int)(pos.y - offset1);
		int rect1Right = rect1Left + listPlantTypes[typeID].size - 1;
		int rect1Bottom = rect1Top + listPlantTypes[typeID].size - 1;

		int rect2Left = x;
		int rect2Top = y;
		int rect2Right = rect2Left + size - 1;
		int rect2Bottom = rect2Top + size - 1;

		return ((rect1Left > rect2Right || rect2Left > rect1Right ||
			 rect1Top > rect2Bottom || rect2Top > rect1Bottom) == false);
	}

	return false;
}

float Plant::computeOffset()
{
	if(typeID > -1 && typeID < listPlantTypes.size())
	{
		return (listPlantTypes[typeID].size - 1) / 2.0f;
	}
	return 0.0f;
}



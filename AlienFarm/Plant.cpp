#include "Plant.h"



Plant::Plant(SDL_Renderer* renderer, Vector2D setPos) :
	pos(setPos), timerGrowth(7.5f + MathAddon::randFloat() * 7.5f), timerMoveUpAndDown(2.0f, MathAddon::randFloat() * 2.0f)
{
	textureSmallMain = TextureLoader::loadTexture(renderer, "Plant 1 Small.bmp");
	textureSmallShadow = TextureLoader::loadTexture(renderer, "Plant 1 Small Shadow.bmp");
	textureMain = TextureLoader::loadTexture(renderer, "Plant 1.bmp");
	textureShadow = TextureLoader::loadTexture(renderer, "Plant 1 Shadow.bmp");
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

Vector2D Plant::getPos()
{
	return pos;
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



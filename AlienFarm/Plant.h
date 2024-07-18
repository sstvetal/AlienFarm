#pragma once
#include <vector>
#include "SDL2/SDL.h"
#include "TextureLoader.h"
#include "Vector2D.h"
#include "Timer.h"
#include "MathAddon.h"
#include "Level.h"


class Plant
{
private:
	struct Type
	{
		std::string name = "";
		int size = 1;
		bool growsOnWetDirt = true;
	};

public:
	Plant(SDL_Renderer* renderer, int setTypeID, Vector2D setPos);
	void update(float dT);
	void draw(SDL_Renderer* renderer, int tileSize);
	void drawShadow(SDL_Renderer* renderer, int tileSize);
	bool checkOverlapWithPlantTypeID(int x, int y, int plantTypeID);
	bool checkOverlapWithMouse(int x, int y);
	bool checkIfTilesUnderOK(Level& level);
	static bool checkIfTilesUnderOkForType(int x, int y, int plantTypeID, Level& level);

private:
	void drawTexture(SDL_Renderer* renderer, SDL_Texture* textureSelected, int tileSize);
	bool checkOverlap(int x, int y, int size);
	float computeOffset();

	Vector2D pos;
	float fDrawScale = 1.0f;
	Timer  timerGrowth, timerMoveUpAndDown;


	int typeID;


	SDL_Texture* textureSmallMain = nullptr, * textureSmallShadow = nullptr,
		* textureMain = nullptr, * textureShadow = nullptr;

	static const std::vector<Type> listPlantTypes;

};
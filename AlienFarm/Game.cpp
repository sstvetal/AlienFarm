#include "Game.h"


Game::Game(SDL_Window* window, SDL_Renderer* renderer, int windowWidth, int windowHeight) :
    placementModeCurrent(PlacementMode::tiles),
    level(renderer, windowWidth / tileSize + (windowWidth % tileSize > 0),
        windowHeight / tileSize + (windowHeight % tileSize > 0))
{
    //Run the game.
    if (window != nullptr && renderer != nullptr) 
    {
        //Store the current times for the clock.
        auto time1 = std::chrono::system_clock::now();
        auto time2 = std::chrono::system_clock::now();


        //Start the game loop and run until it's time to stop.
        bool running = true;
        while (running) {
            //Determine how much time has elapsed since the last frame.
            time2 = std::chrono::system_clock::now();
            std::chrono::duration<float> timeDelta = time2 - time1;
            float timeDeltaFloat = timeDelta.count();

            //Store the new time for the next frame.
            time1 = time2;

            //The amount of time for each frame (no longer than 20 fps).
            const float dT = std::min(timeDeltaFloat, 1.0f / 20.0f);

            processEvents(renderer, running);
            update(dT);
            draw(renderer);
        }
    }
}


Game::~Game() {
    //Clean up.
    TextureLoader::deallocateTextures();
}



void Game::processEvents(SDL_Renderer* renderer, bool& running) 
{
    bool mouseDownThisFrame = false;

    //Process events.
    SDL_Event event;
    while (SDL_PollEvent(&event)) 
    {
        switch (event.type) 
        {
        case SDL_QUIT:
            running = false;
            break;

        case SDL_MOUSEBUTTONDOWN:
            mouseDownThisFrame = (mouseDownStatus == 0);
            if (event.button.button == SDL_BUTTON_LEFT)
                mouseDownStatus = SDL_BUTTON_LEFT;
            else if (event.button.button == SDL_BUTTON_RIGHT)
                mouseDownStatus = SDL_BUTTON_RIGHT;
            break;
        case SDL_MOUSEBUTTONUP:
            mouseDownStatus = 0;
            break;

        case SDL_KEYDOWN:
            switch (event.key.keysym.scancode) 
            {
                //Quit the game.
            case SDL_SCANCODE_ESCAPE:
                running = false;
                break;
            

            //Select the levels tileTypeIDSelected
            case SDL_SCANCODE_1:
            case SDL_SCANCODE_2:
            case SDL_SCANCODE_3:
            case SDL_SCANCODE_4:
            case SDL_SCANCODE_5:
            case SDL_SCANCODE_6:
            case SDL_SCANCODE_7:
            {int tileTypeID = event.key.keysym.scancode - SDL_SCANCODE_1;
            level.setTileTypeIDSelected(tileTypeID);
            placementModeCurrent = PlacementMode::tiles; }
              break;
 
                //Select the plant.
            case SDL_SCANCODE_Q:
                placementModeCurrent = PlacementMode::plants;
                break;
            }
        }
    }


    //Process input from the mouse cursor.
    int mouseX = 0, mouseY = 0;
    SDL_GetMouseState(&mouseX, &mouseY);
    //Convert from the window's coordinate system to the game's coordinate system.
    Vector2D posMouse((float)mouseX / tileSize, (float)mouseY / tileSize);

    if (mouseDownStatus > 0) 
    {
        //The mouse was pressed.
         switch (mouseDownStatus)
         {
         case SDL_BUTTON_LEFT:
             switch (placementModeCurrent)
             {
             case PlacementMode::tiles:
                 level.placeTileTypeIDSelected((int)posMouse.x, (int)posMouse.y);
                 break;
             case PlacementMode::plants:
                 addPlant(renderer, posMouse);
                 break;
             }
             break;

         case SDL_BUTTON_RIGHT:
             removePlantsAtMousePosition(posMouse);
             break;
         }
    }
}



void Game::update(float dT) 
{
    for (auto& plantSelected : listPlants)
    {
        plantSelected.update(dT);
    }
}



void Game::draw(SDL_Renderer* renderer) 
{
    //Draw.
    //Set the background color.
    SDL_SetRenderDrawColor(renderer, 255, 100, 0, 0);
    //Clear the screen.
    SDL_RenderClear(renderer);


    level.draw(renderer, tileSize);

    for(auto& plantsSelected : listPlants)
    {
        plantsSelected.draw(renderer, tileSize);
    }

    //Send the image to the window.
    SDL_RenderPresent(renderer);
}

void Game::addPlant(SDL_Renderer* renderer, Vector2D posMouse)
{
    bool foundPlant = false;

    for (auto it = listPlants.begin(); it != listPlants.end() && foundPlant == false; it++)
    {
        if  ((int)(*it).getPos().x == (int)posMouse.x &&
             (int)(*it).getPos().y == (int)posMouse.y)
             foundPlant = true;
    }

    if(foundPlant == false)
    {
        float randOffsetX = (MathAddon::randFloat() * 2.0f - 1.0f) * 0.1f;
        float randOffsetY = (MathAddon::randFloat() * 2.0f - 1.0f) * 0.1f;



        Vector2D pos((int)posMouse.x + 0.5f + randOffsetX, (int)posMouse.y + 0.5f + randOffsetY);
        listPlants.push_back(Plant(renderer, pos));
    }

}


void Game::removePlantsAtMousePosition(Vector2D posMouse)
{
    for (auto it = listPlants.begin(); it != listPlants.end();)
    {
        if  ((int)(*it).getPos().x == (int)posMouse.x &&
             (int)(*it).getPos().y == (int)posMouse.y)
            it = listPlants.erase(it);
        else
        {
            it++;
        }
    }
}

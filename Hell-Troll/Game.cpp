#include "Game.h"
#include "TextureManager.h"

SDL_Texture* playerTexture;
SDL_Rect srcR, destR;

Game::Game()
{

}

Game::~Game() {}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen)
{

    int flags = 0;
    if(fullscreen)
    {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if(SDL_Init(SDL_INIT_EVERYTHING) == 0)
    {
        std::cout<<"SDL created successfully" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if(window)
        {
            std::cout<<"Window created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, 0);
        if(renderer)
        {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout<<"Render created" << std::endl;
        }
        isRunning = true;
    }
    playerTexture = TextureManger::LoadTexture("Assets/Images/herochar_idle_anim_strip_4-0.png", renderer);
}

void Game::handleEvents()
{
    SDL_Event event;
    SDL_PollEvent(&event);
    switch(event.type)
    {
    case SDL_QUIT :
        isRunning = false;
        break;
    default :
        break;
    }
}

void Game::update()
{
    cnt++;
    std::cout<<cnt<<std::endl;

    destR.h = 64;
    destR.w = 64;
    destR.x = cnt;
}

void Game::render()
{
    SDL_RenderClear(renderer);

    //Add stuff to render
    SDL_RenderCopy(renderer, playerTexture, NULL, &destR);

    SDL_RenderPresent(renderer);
}

void Game::clean()
{
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout<<"Game cleaned" << std::endl;
}

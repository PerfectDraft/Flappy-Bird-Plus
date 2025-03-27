#include "Game.h"
#include "TextureManager.h"
#include "GameObject.h"
#include "Map.h"
#include "Dot.h"

Dot* dot;
GameObject* player;
GameObject* enemy;
Map* map;

SDL_Renderer* Game::renderer = nullptr;

Game::Game() {}

Game::~Game() {
    delete player;
    delete enemy;
    delete map;
}

void Game::init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen) {
    int flags = 0;
    if (fullscreen) {
        flags = SDL_WINDOW_FULLSCREEN;
    }
    if (SDL_Init(SDL_INIT_EVERYTHING) == 0) {
        std::cout << "SDL created successfully" << std::endl;

        window = SDL_CreateWindow(title, xpos, ypos, width, height, flags);

        if (window) {
            std::cout << "Window created" << std::endl;
        }
        renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
        if (renderer) {
            SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
            std::cout << "Render created" << std::endl;
        }
        isRunning = true;
        player = new GameObject("Assets/Images/herochar_idle_anim_strip_4-0.png", 200, 200,
                                "Assets/Images/Dung_yen");;
        enemy = new GameObject("Assets/Images/bomber_goblin_idle_anim_strip_4-1.png", 100, 0);
        map = new Map();
    } else {
        printf("SDL could not be initialize! SDL error: %s\n", SDL_GetError());
    }
}

void Game::handleEvents() {
    SDL_Event event;
    player_dx = 0;  // Reset hướng di chuyển của player
    player_dy = 0;
    enemy_dx = 0;   // Reset hướng di chuyển của enemy
    enemy_dy = 0;

    while (SDL_PollEvent(&event)) {
        if(event.type == SDL_QUIT){
            isRunning = false;
            break;
        }
        else if(event.type == SDL_KEYDOWN){
            switch (event.key.keysym.sym) {
            // Phím mũi tên: điều khiển player
            case SDLK_UP:
                player_dy = -1;
                break;
            case SDLK_DOWN:
                player_dy = 1;
                break;
            case SDLK_LEFT:
                player_dx = -1;
                break;
            case SDLK_RIGHT:
                player_dx = 1;
                break;
            // Phím WASD: điều khiển enemy
            case SDLK_w:
                enemy_dy = -1;
                break;
            case SDLK_s:
                enemy_dy = 1;
                break;
            case SDLK_a:
                enemy_dx = -1;
                break;
            case SDLK_d:
                enemy_dx = 1;
                break;
            }
            break;
        default:
            break;
        }
        dot->handleEvent( e );
    }
}

void Game::update() {
    player->UpdateWithKeys(player_dx, player_dy, map);
    enemy->UpdateWithKeys(enemy_dx, enemy_dy, map);
    dot->move();
}

void Game::render() {
    SDL_RenderClear(renderer);
    map->drawMap();
    player->Render();
    enemy->Render();
    dot->render();
    SDL_RenderPresent(renderer);
}

void Game::clean() {
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    std::cout << "Game cleaned" << std::endl;
}

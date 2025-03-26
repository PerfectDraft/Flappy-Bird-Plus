#ifndef GAME_H_INCLUDED
#define GAME_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include "Map.h"

class Map;

class Game {
public:
    Game();
    ~Game();

    void init(const char* title, int xpos, int ypos, int width, int height, bool fullscreen);
    void handleEvents();
    void update();
    void render();
    void clean();

    bool running() { return isRunning; }

    static SDL_Renderer* renderer;

private:
    int cnt = 0;
    bool isRunning;
    SDL_Window* window;
    Map* map;

    // Hướng di chuyển riêng cho player và enemy
    int player_dx = 0, player_dy = 0;  // Cho player (phím mũi tên)
    int enemy_dx = 0, enemy_dy = 0;    // Cho enemy (WASD)
};

#endif // GAME_H_INCLUDED

#ifndef MAP_H_INCLUDED
#define MAP_H_INCLUDED

#include "Game.h"

class Map {
public:
    Map();
    ~Map();

    void loadMap(int arr[20][25]);
    void drawMap();
    int GetTile(int x, int y);

private:
    SDL_Rect src, dest;

    SDL_Texture* dirt;
    SDL_Texture* grass;
    SDL_Texture* water;

    int map[20][25];
};

#endif // MAP_H_INCLUDED

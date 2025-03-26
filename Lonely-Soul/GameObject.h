#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Game.h"
#include "Map.h"

class GameObject {
public:
    GameObject(const char* textureSheet, int x, int y);
    ~GameObject();

    void Update();
    void UpdateWithKeys(int dx, int dy, Map* map);
    void Render();

private:
    int xpos, ypos;
    int speed = 5;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;

    bool CanMoveTo(int newX, int newY, Map* map);
};

#endif // GAMEOBJECT_H_INCLUDED

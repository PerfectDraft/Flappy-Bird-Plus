#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Game.h"

class GameObject{
public:
    GameObject(const char* textureSheet, SDL_Renderer* ren, int x, int y);
    ~GameObject();

    void Update();
    //Moi doi tuong co hanh vi cap nhat cua rieng minh
    void Render();


private:
    int xpos, ypos;

    SDL_Texture* objTexture;
    SDL_Rect srcRect, destRect;
    SDL_Renderer* renderer;


};

#endif // GAMEOBJECT_H_INCLUDED

#ifndef TEXTUREMANAGER_H_INCLUDED
#define TEXTUREMANAGER_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>

class TextureManger{
public:
    static SDL_Texture* LoadTexture(const char* fileName, SDL_Renderer* ren);
};

#endif // TEXTUREMANAGER_H_INCLUDED

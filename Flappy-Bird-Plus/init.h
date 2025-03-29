#ifndef INIT_H
#define INIT_H

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <string>

using namespace std;

bool init();
SDL_Texture *loadTexture(const string &filePath);
SDL_Texture *createTextTexture(const string &text, SDL_Color color);
bool loadLoadingResources();
bool loadGameResources();
void close();

#endif // INIT_H
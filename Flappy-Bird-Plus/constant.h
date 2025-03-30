#ifndef CONSTANT_H_INCLUDED
#define CONSTANT_H_INCLUDED

#include <SDL.h>
#include <SDL_image.h>
#include <SDL_ttf.h>
#include <SDL_mixer.h>

const int WINDOW_WIDTH = 800;
const int WINDOW_HEIGHT = 600;
const int BIRD_DIMENSION = 40;
const int PIPE_WIDTH = 80;
const int PIPE_GAP_HEIGHT = 200;
const int PIPE_HORIZONTAL_SPEED = 2;
const int MAX_PIPE_COUNT = 3;
const int PIPE_VERTICAL_SPEED = 1;
const int PIPE_VERTICAL_RANGE = 100;

extern SDL_Window *gameWindow;
extern SDL_Renderer *gameRenderer;
extern TTF_Font *gameFont;
extern SDL_Texture *textureBird;
extern SDL_Texture *texturePipeTop;
extern SDL_Texture *texturePipeBottom;
extern SDL_Texture *textureBackground;
extern SDL_Texture *textureMenuBackground;
extern SDL_Texture *textureHighScoreBackground;
extern SDL_Texture *loadingScreenTexture;

extern Mix_Chunk *soundFlap;
extern Mix_Chunk *soundHit;
extern Mix_Music *musicMenu;
extern Mix_Music *musicGame;
extern Mix_Music *musicLoading;

enum GameState { STATE_MENU, STATE_PLAYING, STATE_GAME_OVER, STATE_HIGH_SCORE, STATE_TUTORIAL };

extern GameState currentGameState;
extern int currentScore;
extern int recordScore;


#endif

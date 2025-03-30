#include "init.h"
#include "constant.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <iostream>
#include <string>

using namespace std;

extern SDL_Window *gameWindow;
extern SDL_Renderer *gameRenderer;
extern SDL_Texture *textureBird;
extern SDL_Texture *texturePipeTop;
extern SDL_Texture *texturePipeBottom;
extern SDL_Texture *textureBackground;
extern SDL_Texture *textureMenuBackground;
extern SDL_Texture *textureHighScoreBackground;
extern SDL_Texture *loadingScreenTexture;
extern SDL_Texture *textureGameOverBackground;
extern TTF_Font *gameFont;

extern Mix_Chunk *soundFlap;
extern Mix_Chunk *soundHit;
extern Mix_Music *musicMenu;
extern Mix_Music *musicGame;
extern Mix_Music *musicLoading;
extern Mix_Chunk *soundPoint;

bool init() {
  bool success = true;

  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
    success = false;
  } else {
    if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1")) {
      printf("Warning: Linear texture filtering not enabled!");
    }
    gameWindow = SDL_CreateWindow("Flappy Bird Plus", SDL_WINDOWPOS_CENTERED,
                                  SDL_WINDOWPOS_CENTERED, WINDOW_WIDTH,
                                  WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    if (gameWindow == NULL) {
      printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
      success = false;
    } else {
      gameRenderer = SDL_CreateRenderer(
          gameWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
      if (gameRenderer == NULL) {
        printf("Renderer could not be created! SDL Error: %s\n",
               SDL_GetError());
        success = false;
      } else {
        SDL_SetRenderDrawColor(gameRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

        int imgFlags = IMG_INIT_PNG;
        if (!(IMG_Init(imgFlags) & imgFlags)) {
          printf("SDL_image could not initialize! SDL_image Error: %s\n",
                 IMG_GetError());
          success = false;
        }
        if (TTF_Init() < 0) {
          printf("SDL ttf could not initialize! SDL_ttf Error: %s\n",
                 TTF_GetError());
          success = false;
        } else {
          gameFont = TTF_OpenFont("Assets/Fonts/font.TTF", 24);
          if (!gameFont) {
            printf("Could not load font! Path error! %s\n");
            success = false;
          }
        }
      }
    }

    // Initialize SDL mixer
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
      printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n",
             Mix_GetError());
      success = false;
    }

    // Load icon of the window
    SDL_Surface *iconSurface = IMG_Load("Assets/Images/icon.png");
    if (iconSurface == NULL) {
      printf("Failed to load icon! SDL_image Error: %s\n", IMG_GetError());
    } else {
      SDL_SetWindowIcon(gameWindow, iconSurface);
      SDL_FreeSurface(iconSurface);
    }
  }

  return success;
}

// Load texture
SDL_Texture *loadTexture(const string &filePath) {
  SDL_Surface *surface = IMG_Load(filePath.c_str());
  SDL_Texture *texture = SDL_CreateTextureFromSurface(gameRenderer, surface);
  SDL_FreeSurface(surface);
  return texture;
}

// Created text on window
SDL_Texture *createTextTexture(const string &text, SDL_Color color) {
  SDL_Surface *surface = TTF_RenderText_Solid(gameFont, text.c_str(), color);
  SDL_Texture *texture = SDL_CreateTextureFromSurface(gameRenderer, surface);
  SDL_FreeSurface(surface);
  return texture;
}

// image and music on loading screen
bool loadLoadingResources() {
  bool success = true;
  loadingScreenTexture = loadTexture("Assets/Images/loading_screen.png");
  if (!loadingScreenTexture) {
    cout << "Failed to load loading screen texture" << endl;
    success = false;
  }
  musicLoading = Mix_LoadMUS("Assets/MusicBackground/loading.mp3");
  if (musicLoading == NULL) {
    printf("Failed to load loading music! SDL_mixer Error: %s\n",
           Mix_GetError());
    success = false;
  }
  return success;
}

bool loadGameResources() {
  bool success = true;

  // load images
  textureBird = loadTexture("Assets/Images/bird.png");
  if (!textureBird) {
    cout << "Failed to load bird texture" << endl;
    success = false;
  }
  texturePipeTop = loadTexture("Assets/Images/top_pipe.png");
  if (!texturePipeTop) {
    cout << "Failed to load pie top texture" << endl;
    success = false;
  }
  texturePipeBottom = loadTexture("Assets/Images/bottom_pipe.png");
  if (!texturePipeBottom) {
    cout << "Failed to load pie bottom texture" << endl;
    success = false;
  }
  textureBackground = loadTexture("Assets/Images/background.png");
  if (!textureBackground) {
    cout << "Failed to load background texture" << endl;
    success = false;
  }
  textureMenuBackground = loadTexture("Assets/Images/loading_screen.png");
  if (!textureMenuBackground) {
    cout << "Failed to load menu background texture" << endl;
    success = false;
  }
  textureHighScoreBackground = loadTexture("Assets/Images/scoreHistory.jpg");
  if (!textureHighScoreBackground) {
    cout << "Failed to load high score background" << endl;
    success = false;
  }
  textureGameOverBackground =
      loadTexture("Assets/Images/game_over_background.png");
  if (!textureGameOverBackground) {
    cout << "Failed to load game over background texture" << endl;
    success = false;
  }

  // load sounds
  soundFlap = Mix_LoadWAV("Assets/Sounds/wing.ogg");
  if (soundFlap == NULL) {
    printf("Failed to load flap sound effect! SDL_mixer Error: %s\n",
           Mix_GetError());
    success = false;
  }
  soundHit = Mix_LoadWAV("Assets/Sounds/hit.ogg");
  if (soundHit == NULL) {
    printf("Failed to load hit sound effect! SDL_mixer Error: %s\n",
           Mix_GetError());
    success = false;
  }
  soundPoint = Mix_LoadWAV("Assets/Sounds/point.ogg");
  if (soundPoint == NULL) {
    printf("Failed to load point sound effect! SDL_mixer Error: %s\n",
           Mix_GetError());
    success = false;
  }
  // load music
  musicMenu = Mix_LoadMUS("Assets/MusicBackground/Main_menu.mp3");
  if (musicMenu == NULL) {
    printf("Failed to load menu music! SDL_mixer Error: %s\n", Mix_GetError());
    success = false;
  }
  musicGame = Mix_LoadMUS("Assets/MusicBackground/In_game.mp3");
  if (musicGame == NULL) {
    printf("Failed to load game music! SDL_mixer Error: %s\n", Mix_GetError());
    success = false;
  }
  return success;
}

void close() {
  SDL_DestroyTexture(textureBird);
  if (texturePipeTop)
    SDL_DestroyTexture(texturePipeTop);
  if (texturePipeBottom)
    SDL_DestroyTexture(texturePipeBottom);
  if (textureBackground)
    SDL_DestroyTexture(textureBackground);
  if (textureMenuBackground)
    SDL_DestroyTexture(textureMenuBackground);
  if (textureHighScoreBackground)
    SDL_DestroyTexture(textureHighScoreBackground);
  if (textureGameOverBackground)
    SDL_DestroyTexture(textureGameOverBackground);
  if (gameFont)
    TTF_CloseFont(gameFont);
  if (gameRenderer)
    SDL_DestroyRenderer(gameRenderer);
  if (gameWindow)
    SDL_DestroyWindow(gameWindow);
  IMG_Quit();
  TTF_Quit();
  SDL_Quit();
    //Free sound effect
  Mix_FreeChunk(soundFlap);
  Mix_FreeChunk(soundHit);
  Mix_FreeChunk(soundPoint);

  Mix_FreeMusic(musicMenu);
  Mix_FreeMusic(musicGame);
  Mix_CloseAudio();
}

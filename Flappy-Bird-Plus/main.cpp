#include "constant.h"
#include "game_logic.h"
#include "init.h"
#include "render.h"
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>
#include <SDL_ttf.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

using namespace std;

SDL_Window *gameWindow = NULL;
SDL_Renderer *gameRenderer = NULL;
SDL_Texture *textureBird = NULL;
SDL_Texture *texturePipeTop = NULL;
SDL_Texture *texturePipeBottom = NULL;
SDL_Texture *textureBackground = NULL;
SDL_Texture *textureMenuBackground = NULL;
SDL_Texture *textureHighScoreBackground = NULL;
SDL_Texture *loadingScreenTexture = NULL;
SDL_Texture *textureGameOverBackground = NULL;
TTF_Font *gameFont = NULL;

Mix_Chunk *soundFlap = NULL;
Mix_Chunk *soundHit = NULL;
Mix_Music *musicMenu = NULL;
Mix_Music *musicGame = NULL;
Mix_Music *musicLoading = NULL;
Mix_Chunk *soundPoint = NULL;

GameState currentGameState = STATE_MENU;
int currentScore = 0;
int recordScore = 0;

//main loop
int main(int argc, char *argv[]) {
  srand(static_cast<unsigned int>(time(NULL)));

  if (!init()) {
    cerr << "Initialization failed." << endl;
    return 1;
  }

  if (!loadLoadingResources()) {
    cerr << "Failed to load loading resources." << endl;
    close();
    return 1;
  }

  Mix_PlayMusic(musicLoading, -1);

  // Simulation loading progess
  for (int progress = 0; progress <= 100; progress += 10) {
    drawLoadingScreen(progress);
    SDL_Delay(100); //Simulation time load
  }

  Mix_HaltMusic();
  Mix_PlayMusic(musicMenu, -1);

  if (!loadGameResources()) {
    cerr << "Failed to load resources." << endl;
    close();
    return 1;
  }

  recordScore = loadHighScore(); // Load high score

  bool isRunning = true;
  FlappyBird bird = {WINDOW_WIDTH / 4, WINDOW_HEIGHT / 2, 0};
  GamePipe pipes[MAX_PIPE_COUNT];
  int pipeCount = MAX_PIPE_COUNT;
  for (int i = 0; i < pipeCount; i++) {
    pipes[i].posX = WINDOW_WIDTH + i * (WINDOW_WIDTH / pipeCount);
    pipes[i].posY = rand() % (WINDOW_HEIGHT - PIPE_GAP_HEIGHT - 100) + 50;
    pipes[i].initialPosY = pipes[i].posY;
    pipes[i].verticalDirection = (rand() % 2 == 0) ? 1 : -1;
    pipes[i].isPassed = false;
  }

  while (isRunning) {
    processPlayerInput(isRunning, bird, pipes, pipeCount);

    if (currentGameState == STATE_PLAYING) {
      bool isGameOver = false;
      int previousScore = currentScore;
      refreshGameState(bird, pipes, pipeCount, isGameOver);
      drawGameScene(bird, pipes, pipeCount);

      if (currentScore > previousScore) {
        Mix_PlayChannel(-1, soundPoint, 0);
      }

      if (isGameOver) {
        currentGameState = STATE_GAME_OVER;
      }
    } else if (currentGameState == STATE_MENU) {
      drawMenuScreen();
    } else if (currentGameState == STATE_GAME_OVER) {
      drawGameOverScreen();
    } else if (currentGameState == STATE_HIGH_SCORE) {
      drawHighScoreScreen();
    } else if (currentGameState == STATE_TUTORIAL) {
      drawTutorialScreen();
    }

    SDL_Delay(16);
  }

  saveHighScore(recordScore); // Save high score

  close();
  return 0;
}

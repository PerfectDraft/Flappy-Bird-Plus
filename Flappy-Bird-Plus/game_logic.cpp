#include "game_logic.h"
#include "constant.h"
#include "init.h"
#include <SDL.h>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <iostream>

using namespace std;

extern SDL_Window *gameWindow;
extern SDL_Renderer *gameRenderer;
extern SDL_Texture *textureBackground;
extern Mix_Chunk *soundFlap;
extern Mix_Chunk *soundHit;
extern Mix_Music *musicMenu;
extern Mix_Music *musicGame;
extern Mix_Chunk *soundPoint;

extern GameState currentGameState;
extern int currentScore;
extern int recordScore;

bool detectCollision(const FlappyBird &bird, const GamePipe &pipe) {
  if ((bird.posX + BIRD_DIMENSION > pipe.posX &&
       bird.posX < pipe.posX + PIPE_WIDTH) &&
      ((bird.posY < pipe.posY) ||
       (bird.posY + BIRD_DIMENSION > pipe.posY + PIPE_GAP_HEIGHT))) {
    return true;
  }
  return false;
}

void processPlayerInput(bool &isRunning, FlappyBird &bird, GamePipe pipes[],
                        int &pipeCount) {
  SDL_Event event;
  while (SDL_PollEvent(&event) != 0) {
    if (event.type == SDL_QUIT) {
      isRunning = false;
    } else if (event.type == SDL_KEYDOWN) {
      switch (event.key.keysym.sym) {
      case SDLK_SPACE:
        if (currentGameState == STATE_MENU) {
          currentGameState = STATE_PLAYING;
          Mix_PlayMusic(musicGame, -1);
          // Reset bird position and velocity
          bird.posX = WINDOW_WIDTH / 4;
          bird.posY = WINDOW_HEIGHT / 2;
          bird.velocity = 0;
          // Reset pipes
          for (int i = 0; i < pipeCount; i++) {
            pipes[i].posX = WINDOW_WIDTH + i * (WINDOW_WIDTH / pipeCount);
            pipes[i].posY =
                rand() % (WINDOW_HEIGHT - PIPE_GAP_HEIGHT - 100) + 50;
            pipes[i].initialPosY = pipes[i].posY;
            pipes[i].verticalDirection = (rand() % 2 == 0) ? 1 : -1;
            pipes[i].isPassed = false;
          }
          // Reset score
          currentScore = 0;
        } else if (currentGameState == STATE_PLAYING) {
          bird.velocity = -5;
          Mix_PlayChannel(-1, soundFlap, 0);
        }
        break;
      case SDLK_p:
        if (currentGameState == STATE_GAME_OVER) {
          currentGameState = STATE_MENU;
          Mix_PlayMusic(musicMenu, -1);
        }
        break;
      case SDLK_h:
        if (currentGameState == STATE_MENU) {
          currentGameState = STATE_HIGH_SCORE;
        }
        break;
      case SDLK_m:
        if (currentGameState == STATE_HIGH_SCORE ||
            currentGameState == STATE_TUTORIAL) {
          currentGameState = STATE_MENU;
        }
        break;
      case SDLK_q:
        isRunning = false;
        break;
      case SDLK_t:
        if (currentGameState == STATE_MENU) {
          currentGameState = STATE_TUTORIAL;
        }
        break;
      }
    } else if (event.type == SDL_WINDOWEVENT) {
      if (event.window.event == SDL_WINDOWEVENT_RESIZED) {
        // Update window size
        int newWidth = event.window.data1;
        int newHeight = event.window.data2;
        SDL_SetWindowSize(gameWindow, newWidth, newHeight);
        // Update renderer viewport
        SDL_RenderSetViewport(gameRenderer, NULL);
        // Update background size
        SDL_Rect backgroundRect = {0, 0, newWidth, newHeight};
        SDL_RenderCopy(gameRenderer, textureBackground, NULL, &backgroundRect);
      }
    }
  }
}

void refreshGameState(FlappyBird &bird, GamePipe pipes[], int &pipeCount,
                      bool &isGameOver) {
  bird.velocity += 0.5;
  bird.posY += bird.velocity;

  if (bird.posY < 0) {
    bird.posY = 0;
  }

  for (int i = 0; i < pipeCount; i++) {
    if (detectCollision(bird, pipes[i])) {
      isGameOver = true;
      break;
    }

    pipes[i].posX -= PIPE_HORIZONTAL_SPEED;

    pipes[i].posY += pipes[i].verticalDirection * PIPE_VERTICAL_SPEED;

    if (pipes[i].posY < 0 || pipes[i].posY > WINDOW_HEIGHT - PIPE_GAP_HEIGHT) {
      pipes[i].verticalDirection *= -1;
    }

    if (pipes[i].posX < -PIPE_WIDTH) {
      pipes[i].posX = WINDOW_WIDTH;
      pipes[i].posY = rand() % (WINDOW_HEIGHT - PIPE_GAP_HEIGHT - 100) + 50;
      pipes[i].verticalDirection = (rand() % 2 == 0) ? 1 : -1;
      pipes[i].isPassed = false;
    }

    if (!pipes[i].isPassed && pipes[i].posX < bird.posX) {
      pipes[i].isPassed = true;
      currentScore++;
      if (currentScore > recordScore) {
        recordScore = currentScore;
      }
    }
  }

  if (bird.posY + BIRD_DIMENSION > WINDOW_HEIGHT) {
    isGameOver = true;
  }

  if (isGameOver) {
    Mix_PlayChannel(-1, soundHit, 0);
  }
}

int loadHighScore() {
  int highScore = 0;
  std::ifstream file("Assets/Score/HighestScore.txt");
  if (file.is_open()) {
    file >> highScore;
    file.close();
  }
  return highScore;
}

void saveHighScore(int highScore) {
  std::ofstream file("Assets/Score/HighestScore.txt");
  if (file.is_open()) {
    file << highScore;
    file.close();
  }
}

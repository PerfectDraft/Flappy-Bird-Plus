#ifndef GAME_LOGIC_H
#define GAME_LOGIC_H

#include "entities.h"
#include "init.h"
#include <SDL.h>

bool detectCollision(const FlappyBird &bird, const GamePipe &pipe);
void processPlayerInput(bool &isRunning, FlappyBird &bird, GamePipe pipes[],
                        int &pipeCount);
void refreshGameState(FlappyBird &bird, GamePipe pipes[], int &pipeCount,
                      bool &isGameOver);
int loadHighScore();
void saveHighScore(int highScore);

#endif

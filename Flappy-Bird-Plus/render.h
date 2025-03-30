#ifndef RENDER_H
#define RENDER_H

#include "entities.h"
#include "init.h"
#include <SDL.h>
#include <string>

void drawGameScene(const FlappyBird &bird, const GamePipe pipes[],
                   int pipeCount);
void drawGameOverScreen();
void drawMenuScreen();
void drawHighScoreScreen();
void drawTutorialScreen();
void drawLoadingScreen(int progress);

#endif

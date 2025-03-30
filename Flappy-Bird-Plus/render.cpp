#include "render.h"
#include "constant.h"
#include "init.h"
#include <SDL.h>
#include <SDL_ttf.h>
#include <sstream>
#include <string>

using namespace std;

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

extern int currentScore;
extern int recordScore;

void drawGameScene(const FlappyBird &bird, const GamePipe pipes[],
                   int pipeCount) {
  SDL_RenderClear(gameRenderer);

  SDL_Rect backgroundRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  SDL_RenderCopy(gameRenderer, textureBackground, NULL, &backgroundRect);

  int birdWidth = WINDOW_WIDTH / 10;
  int birdHeight = WINDOW_HEIGHT / 10;
  SDL_Rect birdRect = {bird.posX, bird.posY, birdWidth, birdHeight};
  SDL_RenderCopy(gameRenderer, textureBird, NULL, &birdRect);

  for (int i = 0; i < pipeCount; i++) {
    const GamePipe &pipe = pipes[i];
    SDL_Rect topPipeRect = {pipe.posX, 0, PIPE_WIDTH, pipe.posY};
    SDL_RenderCopy(gameRenderer, texturePipeTop, NULL, &topPipeRect);
    SDL_Rect bottomPipeRect = {pipe.posX, pipe.posY + PIPE_GAP_HEIGHT,
                               PIPE_WIDTH,
                               WINDOW_HEIGHT - (pipe.posY + PIPE_GAP_HEIGHT)};
    SDL_RenderCopy(gameRenderer, texturePipeBottom, NULL, &bottomPipeRect);
  }

  SDL_Color textColor = {255, 255, 255, 255};
  ostringstream oss;
  oss << "Score: " << currentScore;
  SDL_Texture *scoreTexture = createTextTexture(oss.str(), textColor);
  int textWidth, textHeight;
  SDL_QueryTexture(scoreTexture, NULL, NULL, &textWidth, &textHeight);

  SDL_Rect textRect = {10, 10, textWidth, textHeight};
  SDL_RenderCopy(gameRenderer, scoreTexture, NULL, &textRect);
  SDL_DestroyTexture(scoreTexture);

  SDL_RenderPresent(gameRenderer);
}

void drawGameOverScreen() {
  SDL_RenderClear(gameRenderer);

  SDL_Rect gameOverBackgroundRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  SDL_RenderCopy(gameRenderer, textureGameOverBackground, NULL,
                 &gameOverBackgroundRect);

  SDL_Color textColor = {255, 255, 255, 255};

  SDL_Texture *gameOverTexture =
      createTextTexture("Game Over! P to play again or Q to quit", textColor);
  int textWidth, textHeight;
  SDL_QueryTexture(gameOverTexture, NULL, NULL, &textWidth, &textHeight);
  SDL_Rect gameOverRect = {WINDOW_WIDTH / 2 - textWidth / 2,
                           WINDOW_HEIGHT / 2 - textHeight / 2 - 150, textWidth,
                           textHeight};
  SDL_RenderCopy(gameRenderer, gameOverTexture, NULL, &gameOverRect);
  SDL_DestroyTexture(gameOverTexture);

  // Display current score
  ostringstream oss;
  oss << "Your Score: " << currentScore;
  SDL_Texture *currentScoreTexture = createTextTexture(oss.str(), textColor);
  SDL_QueryTexture(currentScoreTexture, NULL, NULL, &textWidth, &textHeight);
  SDL_Rect currentScoreRect = {WINDOW_WIDTH / 2 - textWidth / 2,
                               WINDOW_HEIGHT / 2 + textHeight - 150, textWidth,
                               textHeight};
  SDL_RenderCopy(gameRenderer, currentScoreTexture, NULL, &currentScoreRect);
  SDL_DestroyTexture(currentScoreTexture);

  // Display highest score
  oss.str(""); // Delete score before
  oss << "Highest Score: " << recordScore;
  SDL_Texture *highScoreTexture = createTextTexture(oss.str(), textColor);
  SDL_QueryTexture(highScoreTexture, NULL, NULL, &textWidth, &textHeight);
  SDL_Rect highScoreRect = {WINDOW_WIDTH / 2 - textWidth / 2,
                            WINDOW_HEIGHT / 2 + 2 * textHeight - 150, textWidth,
                            textHeight};
  SDL_RenderCopy(gameRenderer, highScoreTexture, NULL, &highScoreRect);
  SDL_DestroyTexture(highScoreTexture);

  SDL_RenderPresent(gameRenderer);
}

void drawMenuScreen() {
  SDL_RenderClear(gameRenderer);

  SDL_Rect menuBackgroundRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  SDL_RenderCopy(gameRenderer, textureMenuBackground, NULL,
                 &menuBackgroundRect);

  SDL_Color textColor = {255, 0, 0, 255};

  SDL_Texture *titleTexture = createTextTexture("Flappy Bird", textColor);
  int textWidth, textHeight;
  SDL_QueryTexture(titleTexture, NULL, NULL, &textWidth, &textHeight);
  SDL_Rect titleRect = {WINDOW_WIDTH / 2 - textWidth / 2, WINDOW_HEIGHT / 4,
                        textWidth, textHeight};
  SDL_RenderCopy(gameRenderer, titleTexture, NULL, &titleRect);
  SDL_DestroyTexture(titleTexture);

  SDL_Texture *playTexture =
      createTextTexture("Press SPACE to Play", textColor);
  SDL_QueryTexture(playTexture, NULL, NULL, &textWidth, &textHeight);
  SDL_Rect playRect = {WINDOW_WIDTH / 2 - textWidth / 2, WINDOW_HEIGHT / 2,
                       textWidth, textHeight};
  SDL_RenderCopy(gameRenderer, playTexture, NULL, &playRect);
  SDL_DestroyTexture(playTexture);

  SDL_Texture *highScoreTexture =
      createTextTexture("Press H to View Highest Scores", textColor);
  SDL_QueryTexture(highScoreTexture, NULL, NULL, &textWidth, &textHeight);
  SDL_Rect highScoreRect = {WINDOW_WIDTH / 2 - textWidth / 2,
                            WINDOW_HEIGHT / 2 + textHeight, textWidth,
                            textHeight};
  SDL_RenderCopy(gameRenderer, highScoreTexture, NULL, &highScoreRect);
  SDL_DestroyTexture(highScoreTexture);

  SDL_Texture *tutorialPromptTexture =
      createTextTexture("Press T to read tutorial", textColor);
  SDL_QueryTexture(tutorialPromptTexture, NULL, NULL, &textWidth, &textHeight);
  SDL_Rect tutorialPromptRect = {WINDOW_WIDTH / 2 - textWidth / 2,
                                 WINDOW_HEIGHT / 2 + 2 * textHeight, textWidth,
                                 textHeight};
  SDL_RenderCopy(gameRenderer, tutorialPromptTexture, NULL,
                 &tutorialPromptRect);
  SDL_DestroyTexture(tutorialPromptTexture);

  SDL_Texture *gameOverTexture =
      createTextTexture("Press Q to quit", textColor);
  SDL_QueryTexture(gameOverTexture, NULL, NULL, &textWidth, &textHeight);
  SDL_Rect gameOverRect = {WINDOW_WIDTH / 2 - textWidth / 2,
                           WINDOW_HEIGHT / 2 - textHeight / 2 + 120, textWidth,
                           textHeight};
  SDL_RenderCopy(gameRenderer, gameOverTexture, NULL, &gameOverRect);
  SDL_DestroyTexture(gameOverTexture);

  SDL_RenderPresent(gameRenderer);
}

void drawHighScoreScreen() {
  SDL_RenderClear(gameRenderer);

  SDL_Rect highScoreBackgroundRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  SDL_RenderCopy(gameRenderer, textureHighScoreBackground, NULL,
                 &highScoreBackgroundRect);

  SDL_Color textColor = {255, 255, 255, 255};

  ostringstream oss;
  oss << "Highest Score: " << recordScore;
  // Custom position of "High Score"
  SDL_Texture *highScoreTexture = createTextTexture(oss.str(), textColor);
  int textWidth, textHeight;
  SDL_QueryTexture(highScoreTexture, NULL, NULL, &textWidth, &textHeight);

  SDL_Rect highScoreRect = {WINDOW_WIDTH / 2 - textWidth / 2,
                            WINDOW_HEIGHT / 2 - textHeight / 2 - 80, textWidth,
                            textHeight};
  SDL_RenderCopy(gameRenderer, highScoreTexture, NULL, &highScoreRect);
  SDL_DestroyTexture(highScoreTexture);

  // Custom position of "M back to menu"
  SDL_Texture *backToMenuTexture =
      createTextTexture("Press M to go back to Menu", textColor);
  SDL_QueryTexture(backToMenuTexture, NULL, NULL, &textWidth, &textHeight);

  SDL_Rect backToMenuRect = {WINDOW_WIDTH / 2 - textWidth / 2,
                             WINDOW_HEIGHT / 2 - textHeight / 2 - 20, textWidth,
                             textHeight};
  SDL_RenderCopy(gameRenderer, backToMenuTexture, NULL, &backToMenuRect);
  SDL_DestroyTexture(backToMenuTexture);

  SDL_RenderPresent(gameRenderer);
}


// Draw Tutorial Screen
void drawTutorialScreen() {
  SDL_RenderClear(gameRenderer);

  SDL_Texture *tutorialTexture = loadTexture("Assets/Images/tutorial.png");
  if (tutorialTexture) {
    SDL_Rect tutorialRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
    SDL_RenderCopy(gameRenderer, tutorialTexture, NULL, &tutorialRect);
    SDL_DestroyTexture(tutorialTexture);
  } else {
    printf("Failed to load tutorial image!\n");
  }

  // Color of tutorial phrase
  SDL_Color textColor = {255, 255, 255, 255};

  // Create font with new size
  TTF_Font *font = TTF_OpenFont("Assets/Fonts/font.ttf",
                                20);
  if (!font) {
    printf("Failed to load font! SDL_ttf Error: %s\n", TTF_GetError());
    return;
  }

  const char *lines[] = {"Your job is to use the SPACE button to make the bird "
                         "jump to avoid the green pipes.",
                         "This is quite easy due to the limited knowledge of "
                         "math and physics of the coder :))",
                         "Good luck!!!"};

  int yOffset = WINDOW_HEIGHT / 2 - 50;
  for (int i = 0; i < 3; ++i) {
    SDL_Surface *textSurface = TTF_RenderText_Solid(font, lines[i], textColor);
    SDL_Texture *instructionTexture =
        SDL_CreateTextureFromSurface(gameRenderer, textSurface);
    int textWidth = textSurface->w;
    int textHeight = textSurface->h;
    SDL_FreeSurface(textSurface);

    SDL_Rect instructionRect = {WINDOW_WIDTH / 2 - textWidth / 2, yOffset,
                                textWidth, textHeight};
    SDL_RenderCopy(gameRenderer, instructionTexture, NULL, &instructionRect);
    SDL_DestroyTexture(instructionTexture);
    yOffset += textHeight + 10;
    //custom line space
  }
  int textWidth, textHeight;
  SDL_Texture *backToMenuTexture =
      createTextTexture("Press M to go back to Menu", textColor);
  SDL_QueryTexture(backToMenuTexture, NULL, NULL, &textWidth, &textHeight);

  SDL_Rect backToMenuRect = {WINDOW_WIDTH / 2 - textWidth / 2,
                             WINDOW_HEIGHT / 2 - textHeight / 2 - 20 + 150,
                             textWidth, textHeight};
  SDL_RenderCopy(gameRenderer, backToMenuTexture, NULL, &backToMenuRect);
  SDL_DestroyTexture(backToMenuTexture);

  TTF_CloseFont(font);
  SDL_RenderPresent(gameRenderer);
}

void drawLoadingScreen(int progress) {
  SDL_RenderClear(gameRenderer);

  SDL_Rect loadingRect = {0, 0, WINDOW_WIDTH, WINDOW_HEIGHT};
  SDL_RenderCopy(gameRenderer, loadingScreenTexture, NULL, &loadingRect);

  // Draw progess bar
  int barWidth = WINDOW_WIDTH * 0.8;
  int barHeight = 20;
  int barX = (WINDOW_WIDTH - barWidth) / 2;
  int barY = WINDOW_HEIGHT - 50;
  SDL_Rect progressBar = {barX, barY, barWidth * progress / 100, barHeight};
  SDL_SetRenderDrawColor(gameRenderer, 0, 255, 0, 255);
  SDL_RenderFillRect(gameRenderer, &progressBar);

  // Draw percent when load game
  SDL_Color textColor = {255, 255, 255, 255};
  ostringstream oss;
  oss << progress << "%";
  SDL_Texture *percentTexture = createTextTexture(oss.str(), textColor);
  int textWidth, textHeight;
  SDL_QueryTexture(percentTexture, NULL, NULL, &textWidth, &textHeight);
  SDL_Rect textRect = {barX + barWidth + 10, barY, textWidth, textHeight};
  SDL_RenderCopy(gameRenderer, percentTexture, NULL, &textRect);
  SDL_DestroyTexture(percentTexture);

  SDL_RenderPresent(gameRenderer);
}

#include <SDL.h>
#include <
#include <SDL_image.h>
#include <stdio.h>
#include <string>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

class LTexture
{
private:
    SDL_Texture* mTexture;
    int mWidth, mHeight;
public:
    LTexture();
    ~LTexture();
    bool loadFromFile(std::string path);
    void free();
    void setColor(Uint8 red, Uint8 green, Uint8 blue);
    void setBlendMode(SDL_BlendMode blending);
    void setAlpha(Uint8 alpha);
    void render(int x, int y, SDL_Rect* clip = NULL, double angle = 0.0, SDL_Point* center = NULL,
                SDL_RendererFlip flip = SDL_FLIP_NONE);
    int getWidth();
    int getHeight();
};

SDL_Window* gWindow = NULL;
SDL_Renderer* gRenderer = NULL;
const int WALKING_ANIMATION_FRAMES = 6; // Số frame của animation
LTexture gArrow;
SDL_Rect gSpriteSheetClip[WALKING_ANIMATION_FRAMES];
LTexture gSpriteTexture;

LTexture::LTexture()
{
    mTexture = NULL;
    mWidth = 0;
    mHeight = 0;
}

LTexture::~LTexture()
{
    free();
}

void LTexture::free()
{
    if (mTexture != NULL)
    {
        SDL_DestroyTexture(mTexture);
        mTexture = NULL;
        mWidth = 0;
        mHeight = 0;
    }
}

void LTexture::setColor(Uint8 red, Uint8 green, Uint8 blue)
{
    SDL_SetTextureColorMod(mTexture, red, green, blue);
}

void LTexture::setBlendMode(SDL_BlendMode blending)
{
    SDL_SetTextureBlendMode(mTexture, blending);
}

void LTexture::setAlpha(Uint8 alpha)
{
    SDL_SetTextureAlphaMod(mTexture, alpha);
}

void LTexture::render(int x, int y, SDL_Rect* clip, double angle, SDL_Point* center, SDL_RendererFlip flip)
{
    SDL_Rect renderQuad = {x, y, mWidth, mHeight};
    if (clip != NULL)
    {
        renderQuad.w = clip->w;
        renderQuad.h = clip->h;
    }
    SDL_RenderCopyEx(gRenderer, mTexture, clip, &renderQuad, angle, center, flip);
}

int LTexture::getHeight()
{
    return mHeight;
}

int LTexture::getWidth()
{
    return mWidth;
}

bool LTexture::loadFromFile(std::string path)
{
    free();
    SDL_Texture* newTexture = NULL;
    SDL_Surface* loadedSurface = IMG_Load(path.c_str());
    if (loadedSurface == NULL)
    {
        printf("Unable to load image %s! SDL error: %s\n", path.c_str(), SDL_GetError());
        return false;
    }
    else
    {
        SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));
        newTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);
        if (newTexture == NULL)
        {
            printf("Failed to create texture from %s! SDL error: %s\n", path.c_str(), SDL_GetError());
        }
        else
        {
            mWidth = loadedSurface->w;
            mHeight = loadedSurface->h;
        }
        SDL_FreeSurface(loadedSurface);
    }
    mTexture = newTexture;
    return mTexture != NULL;
}

bool init()
{
    bool success = true;
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }
        gWindow = SDL_CreateWindow("Hell Troll", SDL_WINDOWPOS_UNDEFINED,
                                   SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                                   SDL_WINDOW_SHOWN);
        if (gWindow == NULL)
        {
            printf("Could not initialize window! SDL error: %s\n", SDL_GetError());
            success = false;
        }
        else
        {
            gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
            if (gRenderer == NULL)
            {
                printf("Renderer could not be created! SDL error: %s\n", SDL_GetError());
                success = false;
            }
            else
            {
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                int imgFlags = IMG_INIT_PNG | IMG_INIT_JPG;
                if (!(IMG_Init(imgFlags) & imgFlags))
                {
                    printf("SDL image could not initialize! SDL error: %s\n", IMG_GetError());
                    success = false;
                }
            }
        }
    }
    return success;
}

bool loadMedia()
{
    bool success = true;
    if (!gSpriteTexture.loadFromFile("Assets/Images/herochar_spritesheet(new)-1.png"))
    {
        printf("Unable to load texture!\n");
        success = false;
    }
    else{
        //Animation 1
        gSpriteSheetClip[0].x = 0;
        gSpriteSheetClip[0].y = 0;
        gSpriteSheetClip[0].w = 16;
        gSpriteSheetClip[0].h = 16;
        //Animation 2
        gSpriteSheetClip[1].x = 16;
        gSpriteSheetClip[1].y = 0;
        gSpriteSheetClip[1].w = 16;
        gSpriteSheetClip[1].h = 16;
        //Animation 3
        gSpriteSheetClip[2].x = 32;
        gSpriteSheetClip[2].y = 0;
        gSpriteSheetClip[2].w = 16;
        gSpriteSheetClip[2].h = 16;
        //Animation 4
        gSpriteSheetClip[3].x = 48;
        gSpriteSheetClip[3].y = 0;
        gSpriteSheetClip[3].w = 16;
        gSpriteSheetClip[3].h = 16;
        //Animation 5
        gSpriteSheetClip[4].x = 64;
        gSpriteSheetClip[4].y = 0;
        gSpriteSheetClip[4].w = 16;
        gSpriteSheetClip[4].h = 16;
        //Animation 6
        gSpriteSheetClip[5].x = 80;
        gSpriteSheetClip[5].y = 0;
        gSpriteSheetClip[5].w = 16;
        gSpriteSheetClip[5].h = 16;
    }
    return success;
}

void close()
{
    gArrow.free();
    SDL_DestroyRenderer(gRenderer);
    SDL_DestroyWindow(gWindow);
    gRenderer = NULL;
    gWindow = NULL;
    IMG_Quit();
    SDL_Quit();
}

int main(int argc, char* argv[])
{
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        if (!loadMedia())
        {
            printf("Failed to load media!\n");
        }
        else
        {
            bool quit = false;
            SDL_Event e;
            int frame = 0;
            double degree = 0;
            SDL_RendererFlip flipType = SDL_FLIP_NONE;
            while (!quit)
            {
                while (SDL_PollEvent(&e) != 0)
                {
                    if (e.type == SDL_QUIT)
                    {
                        quit = true;
                    }
                    else if(e.type == SDL_KEYDOWN){
                        switch(e.key.keysym.sym){
                            case SDLK_a : degree -= 60; break;
                            case SDLK_d : degree += 60; break;
                            case SDLK_q : flipType = SDL_FLIP_HORIZONTAL; break;
                            case SDLK_e : flipType = SDL_FLIP_VERTICAL; break;
                            case SDLK_w : flipType = SDL_FLIP_NONE; break;
                        }
                    }
                }
                SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
                SDL_RenderClear(gRenderer);
                SDL_Rect *currentClip = &gSpriteSheetClip[frame/6];
                gSpriteTexture.render((SCREEN_WIDTH - currentClip->w)/2, (SCREEN_HEIGHT - currentClip->h)/2,
                              currentClip, degree, NULL,  flipType);
                SDL_RenderPresent(gRenderer);
                frame++;
                if(frame/6 >= WALKING_ANIMATION_FRAMES) frame=0;
            }
        }
    }
    close();
    return 0;
}

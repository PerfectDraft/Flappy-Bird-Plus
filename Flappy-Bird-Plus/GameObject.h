#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Game.h"
#include "Map.h"

class GameObject {
public:
    GameObject(const char* textureSheet, int x, int y, const char* idleTextureSheet = nullptr);
    ~GameObject();

    void Update();
    void UpdateWithKeys(int dx, int dy, Map* map);
    void Render();

private:
    int xpos, ypos;
    int speed = 5;

    SDL_Texture* objTexture;
    SDL_Texture* idleTexture;
    SDL_Rect srcRect, destRect;

    enum Direction { UP, DOWN, LEFT, RIGHT, IDLE };
    Direction direction = IDLE;
    int frame = 0;
    int frameCount = 4;           // 4 frame cho mỗi trạng thái
    int frameSpeed = 40;
    int frameCounter = 0;

    // Mảng lưu các clip cho sprite sheet
    SDL_Rect idleClips[4];        // 4 frame cho idle
    SDL_Rect atackClips[4];
    // Nếu có sprite sheet di chuyển, sẽ thêm mảng clip khác

    bool CanMoveTo(int newX, int newY, Map* map);
    void SetupClips();            // Hàm để thiết lập các clip
};

#endif // GAMEOBJECT_H_INCLUDED

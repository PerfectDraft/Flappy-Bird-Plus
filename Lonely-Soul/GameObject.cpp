#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y) {
    objTexture = TextureManger::LoadTexture(textureSheet);
    xpos = x;
    ypos = y;
}

bool GameObject::CanMoveTo(int newX, int newY, Map* map) {
    // Kiểm tra 4 góc của destRect (vì player có kích thước 32x32)
    int tileTopLeft = map->GetTile(newX, newY);  // Góc trên trái
    int tileTopRight = map->GetTile(newX + destRect.w - 1, newY);  // Góc trên phải
    int tileBottomLeft = map->GetTile(newX, newY + destRect.h - 1);  // Góc dưới trái
    int tileBottomRight = map->GetTile(newX + destRect.w - 1, newY + destRect.h - 1);  // Góc dưới phải

    // Nếu bất kỳ góc nào nằm trên nước (0), không cho di chuyển
    if (tileTopLeft == 0 || tileTopRight == 0 || tileBottomLeft == 0 || tileBottomRight == 0) {
        return false;
    }
    return true;  // Nếu không có góc nào trên nước, cho phép di chuyển
}

void GameObject::Update() {
    xpos++;
    ypos++;

    srcRect.h = 16;
    srcRect.w = 16;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::UpdateWithKeys(int dx, int dy, Map* map) {
    int newX = xpos + dx * speed;
    int newY = ypos + dy * speed;

    // Kiểm tra xem có thể di chuyển đến vị trí mới không
    if (CanMoveTo(newX, newY, map)) {
        xpos = newX;
        ypos = newY;
    }

    srcRect.h = 16;
    srcRect.w = 16;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::Render() {
    SDL_RenderCopy(Game::renderer, objTexture, &srcRect, &destRect);
}

GameObject::~GameObject() {
    SDL_DestroyTexture(objTexture);
}

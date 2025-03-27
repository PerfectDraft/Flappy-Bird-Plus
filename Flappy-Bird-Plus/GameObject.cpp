#include "GameObject.h"
#include "TextureManager.h"

GameObject::GameObject(const char* textureSheet, int x, int y, const char* idleTextureSheet) {
    objTexture = TextureManger::LoadTexture(textureSheet);
    idleTexture = (idleTextureSheet != nullptr) ? TextureManger::LoadTexture(idleTextureSheet) : objTexture;

    xpos = x;
    ypos = y;

    srcRect.h = 16;
    srcRect.w = 16;
    srcRect.x = 0;
    srcRect.y = 0;

    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;

    SetupClips();
}

void GameObject::SetupClips() {
    for (int i = 0; i < 4; i++) {
        idleClips[i].x = i * 16;
        idleClips[i].y = 0;
        idleClips[i].w = 16;
        idleClips[i].h = 16;
    }
}

bool GameObject::CanMoveTo(int newX, int newY, Map* map) {
    int tileTopLeft = map->GetTile(newX, newY);
    int tileTopRight = map->GetTile(newX + destRect.w - 1, newY);
    int tileBottomLeft = map->GetTile(newX, newY + destRect.h - 1);
    int tileBottomRight = map->GetTile(newX + destRect.w - 1, newY + destRect.h - 1);

    if (tileTopLeft == 0 || tileTopRight == 0 || tileBottomLeft == 0 || tileBottomRight == 0) {
        return false;
    }
    return true;
}

void GameObject::Update() {
    // Bỏ logic cập nhật srcRect và destRect ở đây
    // Chỉ giữ lại nếu cần logic khác cho các đối tượng không dùng UpdateWithKeys()
}

void GameObject::UpdateWithKeys(int dx, int dy, Map* map) {
    int newX = xpos + dx * speed;
    int newY = ypos + dy * speed;

    // Cập nhật hướng di chuyển
    if (dx == 0 && dy == 0) {
        direction = IDLE;
    } else if (dx > 0) {
        direction = RIGHT;
    } else if (dx < 0) {
        direction = LEFT;
    } else if (dy < 0) {
        direction = UP;
    } else if (dy > 0) {
        direction = DOWN;
    }

    // Cập nhật animation
    frameCounter++;
    if (frameCounter >= frameSpeed) {
        frame = (frame + 1) % frameCount;
        frameCounter = 0;
    }

    // Chọn clip dựa trên trạng thái
    SDL_Rect* currentClip = nullptr;
    if (direction == IDLE) {
        currentClip = &idleClips[frame];
    } else {
        currentClip = &idleClips[frame];  // Hiện tại chỉ có idle, nên dùng idleClips
    }
    srcRect = *currentClip;

    // Cập nhật vị trí nếu có thể di chuyển
    if (CanMoveTo(newX, newY, map)) {
        xpos = newX;
        ypos = newY;
    }

    // Cập nhật destRect
    destRect.x = xpos;
    destRect.y = ypos;
    destRect.w = srcRect.w * 2;
    destRect.h = srcRect.h * 2;
}

void GameObject::Render() {
    SDL_Texture* currentTexture = (direction == IDLE) ? idleTexture : objTexture;
    SDL_RenderCopy(Game::renderer, currentTexture, &srcRect, &destRect);
}

GameObject::~GameObject() {
    SDL_DestroyTexture(objTexture);
    if (idleTexture != objTexture) {
        SDL_DestroyTexture(idleTexture);
    }
}

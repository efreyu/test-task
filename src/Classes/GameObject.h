#ifndef CAR_EXAMPLE_GAMEOBJECT_H
#define CAR_EXAMPLE_GAMEOBJECT_H

#include "sTransform.h"
#include "LoadManager.h"

class GameObject {
public:
    int gameObjectId;
    sTransform transform;
    SDL_Texture *texture{};
    SDL_Rect srcRect{}, destRect{};
    SDL_RendererFlip spriteFlip = SDL_FLIP_NONE;
    bool isActive, isDestroyed, isRides;
    int windowWidth, windowHeight;

    GameObject() {
        Init();
    };

    GameObject(int id, sTransform transformPos) : gameObjectId(id), transform(transformPos) {
        Init();
    }

    void Init() {
        isActive = false;
        isDestroyed = false;
        isRides = false;
        auto [ width, height, scale ] = Game::GetWindowResolution();
        windowWidth = width;
        windowHeight = height;
    }

    ~GameObject() {
        SDL_DestroyTexture(texture);
    }

    bool operator==(const GameObject& gameObject) const
    {
        return gameObjectId == gameObject.gameObjectId;
    }

    bool operator!=(const GameObject& gameObject) const
    {
        return gameObjectId != gameObject.gameObjectId;
    }

    void LoadTexture(const std::string& path) {
        texture = LoadManager::LoadTexture((const char*)path.c_str());
    }

    void UpdateObject() {
        if (transform.x > 0 - transform.height * 2 && transform.x < windowWidth + transform.height * 2 &&
        transform.y > 0 - transform.height * 2 && transform.y < windowHeight + transform.height * 2) {
            Update();
            UpdateTransform();
        } else {
            isActive = false;
            isDestroyed = true;
        }
    }

    virtual sTransform GetNextPosition() { return *new sTransform(); };

    virtual void Update() {}

    void Draw() const {
        LoadManager::DrawFlip(texture, srcRect, destRect, transform.angle, spriteFlip);
    }

private:
    void UpdateTransform() {
        srcRect.x = 0;
        srcRect.y = 0;
        srcRect.w = transform.width;
        srcRect.h = transform.height;
        destRect.w = transform.width * transform.scale;
        destRect.h = transform.height * transform.scale;
        destRect.x = transform.x;
        destRect.y = transform.y;
        //flip sprite
        switch (transform.direction) {
            case eDirection::UP:
                spriteFlip = SDL_FLIP_VERTICAL;
                break;
            case eDirection::RIGHT:
                transform.angle = -90.0;
                break;
            case eDirection::LEFT:
                transform.angle = 90.0;
                break;
            default:
                spriteFlip = SDL_FLIP_NONE;
                transform.angle = 0.0;
        }
    }
};

#endif //CAR_EXAMPLE_GAMEOBJECT_H

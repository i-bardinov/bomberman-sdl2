#include "Entities/Object.h"

namespace bomberman
{
    Object::Object(SDL_Renderer* _renderer)
    {
        this->renderer = _renderer;
    }

    Object::~Object() {}

    void Object::setSize(const int width, const int height)
    {
        rect.w = width;  // controls the width of the rect
        rect.h = height; // controls the height of the rect
    }

    void Object::setPosition(const int x, const int y)
    {
        rect.x = x; // controls the rect's x coordinate
        rect.y = y; // controls the rect's y coordinate
    }

    void Object::setClip(const int width, const int height, const int x, const int y)
    {
        clip.w = width;  // controls the width of the rect
        clip.h = height; // controls the height of the rect
        clip.x = x;      // controls the rect's x coordinate
        clip.y = y;      // controls the rect's y coordinate
    }

    void Object::attachToCamera(bool isAttached /* = true*/)
    {
        this->isAttachedToCamera = isAttached;
    }

    int Object::getWidth() const
    {
        return rect.w;
    }

    int Object::getHeight() const
    {
        return rect.h;
    }

    int Object::getPositionX() const
    {
        return rect.x;
    }

    int Object::getPositionY() const
    {
        return rect.y;
    }

    const SDL_Rect& Object::getRect() const
    {
        return rect;
    }

    void Object::setFlip(SDL_RendererFlip flip)
    {
        flipping = flip;
    }

    void Object::update(const unsigned int /*delta*/) {}

    void Object::draw(const SDL_Rect& camera) const
    {
        if(renderer != nullptr && texture != nullptr)
        {
            // change position according to camera
            SDL_Rect destrinationRect = rect;
            if(isAttachedToCamera)
            {
                destrinationRect.x -= camera.x;
                destrinationRect.y -= camera.y;
            }
            // draw on the screen
            SDL_RenderCopyEx(renderer, texture.get(), &clip, &destrinationRect, 0, nullptr, flipping);
        }
    }
} // namespace bomberman

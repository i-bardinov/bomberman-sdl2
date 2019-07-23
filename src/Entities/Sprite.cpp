#include "Entities/Sprite.h"

namespace bomberman
{
    Sprite::Sprite(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer) : Object(_renderer)
    {
        this->texture = _texture;

        // get width and height of texture;
        int width, height;
        SDL_QueryTexture(texture.get(), NULL, NULL, &width, &height);
        // set clip and rect
        clip.x = 0;
        clip.y = 0;
        clip.w = width;
        clip.h = height;
        rect.x = 0;
        rect.y = 0;
        rect.w = width;
        rect.h = height;
    }

    void Sprite::addAnimation(std::shared_ptr<Animation> animation)
    {
        animations.push_back(animation);
    }

    void Sprite::update(const unsigned int delta)
    {
        for(auto& animation : animations)
        {
            animation->update(delta);
        }
    }
} // namespace bomberman

#include "Core/Animation.h"

#include "Entities/Sprite.h"

namespace bomberman
{
    void Animation::addAnimationEntity(AnimationEntity entity)
    {
        animation.push_back(std::move(entity));
    }

    void Animation::setSprite(Sprite* _sprite)
    {
        this->sprite = _sprite;
    }

    void Animation::setAnimationInterval(const unsigned int timeInMs)
    {
        interval = timeInMs;
    }

    void Animation::play()
    {
        if(isPlaying)
            return;

        isPlaying = true;
        time = interval;
    }

    void Animation::pause()
    {
        isPlaying = false;
    }

    void Animation::reset()
    {
        pause();
        currentEntity = 0;
    }

    void Animation::update(const unsigned int delta)
    {
        if(animation.size() < 1 || !sprite || !isPlaying)
            return;

        time += delta;
        if(time >= interval)
        {
            time = 0;
            AnimationEntity entity = animation[currentEntity];
            currentEntity = (currentEntity + 1) % animation.size();
            sprite->setClip(entity.width, entity.height, entity.positionX, entity.positionY);
        }
    }
} // namespace bomberman

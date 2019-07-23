#ifndef _BOMBERMAN_CORE_ANIMATION_H_
#define _BOMBERMAN_CORE_ANIMATION_H_

#include <vector>

namespace bomberman
{
    class Sprite;
    /**
     * @brief Animation part for clipping
     *
     */
    struct AnimationEntity
    {
        /**
         * @brief Construct a new Animation Entity object
         *
         * @param posX
         * @param posY
         * @param w
         * @param h
         */
        AnimationEntity(const unsigned int posX, const unsigned int posY, const unsigned int w,
                        const unsigned int h)
            : positionX(posX), positionY(posY), width(w), height(h){};

        unsigned int positionX = 0;
        unsigned int positionY = 0;
        unsigned int width = 0;
        unsigned int height = 0;
    };

    /**
     * @brief Animation class
     *
     */
    class Animation
    {
      public:
        /**
         * @brief add entity
         *
         * @param entity
         */
        void addAnimationEntity(AnimationEntity entity);
        /**
         * @brief Set the Sprite to animation for clipping
         *
         * @param sprite - sprite
         */
        void setSprite(Sprite* sprite);
        /**
         * @brief Set the Animation Interval to change clipping
         *
         * @param timeInMs - time in ms
         */
        void setAnimationInterval(const unsigned int timeInMs);
        /**
         * @brief play animation
         *
         */
        void play();
        /**
         * @brief pause animation
         *
         */
        void pause();
        /**
         * @brief reset animation and pause
         *
         */
        void reset();
        /**
         * @briefupdate animation
         *
         * @param delta
         */
        void update(const unsigned int delta);

      private:
        // animation
        std::vector<AnimationEntity> animation;
        unsigned int interval = 100;
        unsigned int time = 0;
        bool isPlaying = false;
        unsigned int currentEntity = 0;
        // sprite clipping
        Sprite* sprite = nullptr;
    };
} // namespace bomberman

#endif // _BOMBERMAN_CORE_ANIMATION_H_

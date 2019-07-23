#ifndef _BOMBERMAN_ENTITIES_SPRITE_H_
#define _BOMBERMAN_ENTITIES_SPRITE_H_

#include <SDL.h>
#include <memory>
#include <vector>

#include "Entities/Object.h"

#include "Core/Animation.h"

namespace bomberman
{
    /**
     * @brief Sprite object - for drawable objects
     *
     */
    class Sprite : public Object
    {
      public:
        /**
         * @brief Construct a new Sprite object
         *
         * @param texture - SDL texture
         * @param renderer - SDL Renderer
         */
        Sprite(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer);
        /**
         * @brief Add animation to sprite
         *
         * @param animation - animation
         */
        void addAnimation(std::shared_ptr<Animation> animation);
        /**
         * @brief Node update
         *
         * @param delta - time in ms
         */
        virtual void update(const unsigned int delta) override;

      private:
        std::vector<std::shared_ptr<Animation>> animations; // array of animations
    };
} // namespace bomberman

#endif // _BOMBERMAN_ENTITIES_SPRITE_H_

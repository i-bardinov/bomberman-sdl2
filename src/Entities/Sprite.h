#ifndef _BOMBERMAN_ENTITIES_SPRITE_H_
#define _BOMBERMAN_ENTITIES_SPRITE_H_

#include <SDL.h>
#include <memory>
#include <vector>

#include "Entities/Object.h"

#include "Core/Animation.h"

namespace bomberman
{
    class Sprite : public Object
    {
      public:
        Sprite(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer);

        void addAnimation(std::shared_ptr<Animation> animation);

        virtual void update(const unsigned int delta) override;

      private:
        std::vector<std::shared_ptr<Animation>> animations;
    };
} // namespace bomberman

#endif // _BOMBERMAN_ENTITIES_SPRITE_H_

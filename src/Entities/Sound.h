#ifndef _BOMBERMAN_ENTITIES_SOUND_H_
#define _BOMBERMAN_ENTITIES_SOUND_H_

#include <SDL_mixer.h>
#include <memory>

namespace bomberman
{
    /**
     * @brief Base class for sound
     *
     */
    class Sound
    {
      public:
        /**
         * @brief Construct a new sound object
         *
         */
        Sound(std::shared_ptr<Mix_Chunk> sound);
        /**
         * @brief Start playing sound
         *
         */
        void play();

      private:
        std::shared_ptr<Mix_Chunk> sound = nullptr; // smart pointer to SDL2 sound
    };
} // namespace bomberman

#endif // _BOMBERMAN_ENTITIES_SOUND_H_

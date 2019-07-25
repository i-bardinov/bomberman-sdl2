#ifndef _BOMBERMAN_ENTITIES_MUSIC_H_
#define _BOMBERMAN_ENTITIES_MUSIC_H_

#include <SDL_mixer.h>
#include <memory>

namespace bomberman
{
    /**
     * @brief Base class for music
     *
     */
    class Music
    {
      public:
        /**
         * @brief Construct a new music object
         *
         */
        Music(std::shared_ptr<Mix_Music> music);
        /**
         * @brief Start playing music
         *
         */
        void play();
        /**
         * @brief Stop current music
         *
         */
        void stop();
        /**
         * @brief Pause current music
         *
         */
        void pause();
        /**
         * @brief Resume music
         *
         */
        void resume();

      private:
        std::shared_ptr<Mix_Music> music = nullptr; // smart pointer to SDL2 music
    };
} // namespace bomberman

#endif // _BOMBERMAN_ENTITIES_MUSIC_H_

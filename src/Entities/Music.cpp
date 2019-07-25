#include <iostream>

#include "Entities/Music.h"

namespace bomberman
{
    Music::Music(std::shared_ptr<Mix_Music> _music)
    {
        this->music = _music;
    }

    void Music::play()
    {
        if(Mix_PlayMusic(music.get(), -1) == -1)
        {
            std::cout << "Music::play() error: " << Mix_GetError() << std::endl;
        }
    }

    void Music::stop()
    {
        Mix_HaltMusic();
    }

    void Music::pause()
    {
        Mix_PauseMusic();
    }

    void Music::resume()
    {
        Mix_ResumeMusic();
    }
} // namespace bomberman

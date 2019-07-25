#include <iostream>

#include "Entities/Sound.h"

namespace bomberman
{
    Sound::Sound(std::shared_ptr<Mix_Chunk> _sound)
    {
        this->sound = _sound;
    }

    void Sound::play()
    {
        if(Mix_PlayChannel(-1, sound.get(), 0) == -1)
        {
            std::cout << "Sound::play() error: " << Mix_GetError() << std::endl;
        }
    }
} // namespace bomberman

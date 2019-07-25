#include <SDL_image.h>
#include <iostream>

#include "Managers/AssetManager.h"

namespace bomberman
{
    void AssetManager::load(SDL_Renderer* renderer)
    {
        // load font
        loadFont();
        // load textures
        loadTexture(renderer, Texture::MenuBack, "assets/menu_title.png");
        loadTexture(renderer, Texture::Stone, "assets/stone.png");
        loadTexture(renderer, Texture::Grass, "assets/grass.png");
        loadTexture(renderer, Texture::Brick, "assets/brick.png");
        loadTexture(renderer, Texture::Player, "assets/player.png");
        loadTexture(renderer, Texture::Enemy1, "assets/enemy_1.png");
        loadTexture(renderer, Texture::Enemy2, "assets/enemy_2.png");
        loadTexture(renderer, Texture::Enemy3, "assets/enemy_3.png");
        loadTexture(renderer, Texture::Bomb, "assets/bomb.png");
        loadTexture(renderer, Texture::Explosion, "assets/explosion.png");
        loadTexture(renderer, Texture::Door, "assets/door.png");
        // load music
        loadMusic(MusicEnum::MainMenu, "assets/main_theme.ogg");
        loadMusic(MusicEnum::Level, "assets/level.ogg");
        // load sounds
        loadSound(SoundEnum::Win, "assets/win.wav");
        loadSound(SoundEnum::Lose, "assets/lose.wav");
        loadSound(SoundEnum::Explosion, "assets/explosion.wav");
    }

    std::shared_ptr<TTF_Font> AssetManager::getFont() const
    {
        return font;
    }

    std::shared_ptr<SDL_Texture> AssetManager::getTexture(Texture texture)
    {
        return textures[texture];
    }

    std::shared_ptr<Mix_Music> AssetManager::getMusic(MusicEnum music)
    {
        return musics[music];
    }

    std::shared_ptr<Mix_Chunk> AssetManager::getSound(SoundEnum sound)
    {
        return sounds[sound];
    }

    void AssetManager::loadFont()
    {
        // load font
        font = std::shared_ptr<TTF_Font>(TTF_OpenFont("assets/font.ttf", 32), TTF_CloseFont);
        if(!font)
        {
            std::cout << "TTF_OpenFont Error: " << TTF_GetError() << std::endl;
        }
    }

    void AssetManager::loadTexture(SDL_Renderer* renderer, Texture texture, const std::string& filePath)
    {
        textures[texture] =
            std::shared_ptr<SDL_Texture>(IMG_LoadTexture(renderer, filePath.c_str()), SDL_DestroyTexture);
        if(!textures[texture])
        {
            std::cout << "IMG_LoadTexture Error: " << IMG_GetError() << std::endl;
        }
    }

    void AssetManager::loadMusic(MusicEnum music, const std::string& filePath)
    {
        musics[music] = std::shared_ptr<Mix_Music>(Mix_LoadMUS(filePath.c_str()), Mix_FreeMusic);
        if(!musics[music])
        {
            std::cout << "loadMusic Error: " << Mix_GetError() << std::endl;
        }
    }

    void AssetManager::loadSound(SoundEnum sound, const std::string& filePath)
    {
        sounds[sound] = std::shared_ptr<Mix_Chunk>(Mix_LoadWAV(filePath.c_str()), Mix_FreeChunk);
        if(!sounds[sound])
        {
            std::cout << "loadSound Error: " << Mix_GetError() << std::endl;
        }
    }
} // namespace bomberman

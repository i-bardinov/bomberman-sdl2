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
        loadTexture(renderer, Texture::EnemyBaloon, "assets/enemy_baloon.png");
        loadTexture(renderer, Texture::EnemyBlue, "assets/enemy_blue.png");
        loadTexture(renderer, Texture::Bomb, "assets/bomb.png");
        loadTexture(renderer, Texture::Bang, "assets/bang.png");
        loadTexture(renderer, Texture::Door, "assets/door.png");
    }

    std::shared_ptr<TTF_Font> AssetManager::getFont() const
    {
        return font;
    }

    std::shared_ptr<SDL_Texture> AssetManager::getTexture(Texture texture)
    {
        return textures[texture];
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
} // namespace bomberman

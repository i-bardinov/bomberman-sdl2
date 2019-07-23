#include <iostream>

#include "Entities/Text.h"

namespace bomberman
{
    Text::Text(std::shared_ptr<TTF_Font> _font, SDL_Renderer* _renderer, const std::string& _text)
        : Object(_renderer)
    {
        this->font = _font;
        this->text = _text;
        // create texture
        loadText();
    }

    void Text::setText(const std::string& _text)
    {
        this->text = _text;
        // reload texture to apply changes
        loadText();
    }

    void Text::setColor(const SDL_Color& _color)
    {
        this->color = _color;
        // reload texture to apply changes
        loadText();
    }

    void Text::loadText()
    {
        if(!font)
        {
            std::cout << "Text::loadText: font is null!" << std::endl;
            return;
        }

        // create surface
        SDL_Surface* surface = TTF_RenderUTF8_Solid(font.get(), text.c_str(), color);
        if(!surface)
        {
            std::cout << "TTF_RenderText_SolidError: " << TTF_GetError() << std::endl;
            return;
        }

        // convert to texture
        texture =
            std::shared_ptr<SDL_Texture>(SDL_CreateTextureFromSurface(renderer, surface), SDL_DestroyTexture);
        if(!texture)
        {
            std::cout << "SDL_CreateTextureFromSurface: " << SDL_GetError() << std::endl;
        }
        else
        {
            // get width and height of texture to set clip
            int width, height;
            SDL_QueryTexture(texture.get(), NULL, NULL, &width, &height);
            clip.x = 0;
            clip.y = 0;
            clip.w = width;
            clip.h = height;
        }
        // free surface
        SDL_FreeSurface(surface);
    }
} // namespace bomberman

#ifndef _BOMBERMAN_ENTITIES_TEXT_H_
#define _BOMBERMAN_ENTITIES_TEXT_H_

#include <SDL_ttf.h>

#include "Entities/Object.h"

namespace bomberman
{
    /**
     * @brief Text object
     *
     */
    class Text : public Object
    {
      public:
        /**
         * @brief Construct a new Text object
         *
         * @param font - SDL2_TTF font
         * @param renderer - SDL2 renderer
         * @param text - text to draw on the screen
         */
        Text(std::shared_ptr<TTF_Font> font, SDL_Renderer* renderer, const std::string& text);
        /**
         * @brief Set the Text
         *
         * @param text - text to draw on the screen
         */
        void setText(const std::string& text);
        /**
         * @brief Set the Color
         *
         * @param color - color of text
         */
        void setColor(const SDL_Color& color);

      private:
        /**
         * @brief load text to texture if text or color was changed
         *
         */
        void loadText();

        std::shared_ptr<TTF_Font> font = nullptr; // SDL2 font
        std::string text;                         // text to display
        SDL_Color color = {255, 255, 255, 255};   // color of text
    };
} // namespace bomberman

#endif // _BOMBERMAN_ENTITIES_TEXT_H_

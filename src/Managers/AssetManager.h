#ifndef _BOMBERMAN_MANAGERS_ASSET_MANAGER_H_
#define _BOMBERMAN_MANAGERS_ASSET_MANAGER_H_

#include <SDL_ttf.h>
#include <memory>
#include <string>
#include <unordered_map>

namespace bomberman
{
    /**
     * @brief Enumeration for Texture
     *
     * @see getTexture
     */
    enum class Texture : int
    {
        MenuBack,
        Stone,
        Grass,
        Brick,
        Player,
        Enemy1,
        Enemy2,
        Enemy3,
        Bomb,
        Bang,
        Door
    };
    /**
     * @brief Hash for Texture enum
     *
     */
    struct EnumClassHash
    {
        template<typename T> std::size_t operator()(T t) const
        {
            return static_cast<std::size_t>(t);
        }
    };

    /**
     * @brief Asset Manager
     *
     */
    class AssetManager
    {
      public:
        /**
         * @brief Load assets
         *
         * @param renderer - SDL2 Renderer
         */
        void load(SDL_Renderer* renderer);
        /**
         * @brief Get font
         *
         * @return std::shared_ptr<TTF_Font> - loaded font
         */
        std::shared_ptr<TTF_Font> getFont() const;
        /**
         * @brief Get textures
         *
         * @param texture - texture enumerator
         *
         * @return std::shared_ptr<SDL_Texture>- loaded texture
         */
        std::shared_ptr<SDL_Texture> getTexture(Texture texture);

      private:
        /**
         * @brief load font
         *
         */
        void loadFont();
        /**
         * @brief load textures
         *
         * @param renderer - SDL2 renderer
         * @param texture - texture enumerator
         * @param filePath - path to file with texture
         */
        void loadTexture(SDL_Renderer* renderer, Texture texture, const std::string& filePath);

        std::shared_ptr<TTF_Font> font = nullptr;                                          // font
        std::unordered_map<Texture, std::shared_ptr<SDL_Texture>, EnumClassHash> textures; // map of textures
    };
} // namespace bomberman

#endif // _BOMBERMAN_MANAGERS_ASSET_MANAGER_H_

#ifndef _BOMBERMAN_ENTITIES_OBJECT_H_
#define _BOMBERMAN_ENTITIES_OBJECT_H_

#include <SDL.h>
#include <memory>

namespace bomberman
{
    /**
     * @brief Base class for objects
     *
     */
    class Object
    {
      public:
        /**
         * @brief Construct a new object
         *
         * @param renderer - SDL2 renderer
         */
        Object(SDL_Renderer* renderer);
        /**
         * @brief Destroy the object
         *
         */
        virtual ~Object();
        /**
         * @brief Set the Size of object
         *
         * @param width
         * @param height
         */
        void setSize(const int width, const int height);
        /**
         * @brief Set the Position of object
         *
         * @param x - position x
         * @param y - position y
         */
        void setPosition(const int x, const int y);
        /**
         * @brief Set the Clip of source texture
         *
         * @param width
         * @param height
         * @param x - position x
         * @param y - position y
         */
        void setClip(const int width, const int height, const int x, const int y);
        /**
         * @brief Attach object to camera movement
         *
         * @param isAttached - attach if true
         */
        void attachToCamera(bool isAttached = true);
        /**
         * @brief Get the Width of object
         *
         * @return int - width
         */
        int getWidth() const;
        /**
         * @brief Get the Height of object
         *
         * @return int - height
         */
        int getHeight() const;
        /**
         * @brief Get the Position X of object
         *
         * @return int - position X
         */
        int getPositionX() const;
        /**
         * @brief Get the Position Y of object
         *
         * @return int - position Y
         */
        int getPositionY() const;
        /**
         * @brief Get Rect of object
         *
         * @return SDL_Rect& - rect
         */
        const SDL_Rect& getRect() const;
        /**
         * @brief Set the Flip object
         *
         * @param flip - flip of texture
         */
        void setFlip(SDL_RendererFlip flip);
        /**
         * @brief Update object
         *
         * @param delta - time in milliseconds
         */
        virtual void update(const unsigned int delta);
        /**
         * @brief Draw object on the screen
         *
         * @param SDL_Rect - camera position
         */
        void draw(const SDL_Rect& camera) const;

      protected:
        SDL_Renderer* renderer = nullptr;               // SDL2 renderer
        std::shared_ptr<SDL_Texture> texture = nullptr; // SDL2 texture
        SDL_Rect rect;                                  // size and position of texture on the screen
        SDL_Rect clip;                                  // what part of texture to draw on the screen
        SDL_RendererFlip flipping = SDL_FLIP_NONE;      // flip of texture

      private:
        bool isAttachedToCamera = true; // follow to camera
    };
} // namespace bomberman

#endif // _BOMBERMAN_ENTITIES_OBJECT_H_

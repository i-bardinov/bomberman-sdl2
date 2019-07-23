#ifndef _BOMBERMAN_ENTITIES_PLAYER_H_
#define _BOMBERMAN_ENTITIES_PLAYER_H_

#include "Entities/Creature.h"

#include "Core/Animation.h"

namespace bomberman
{
    /**
     * @brief Enumeration of movement directions
     *
     */
    enum class MovementDirection
    {
        None,
        Up,
        Down,
        Left,
        Right
    };
    /**
     * @brief Player class
     *
     */
    class Player : public Creature
    {
      public:
        /**
         * @brief Create player
         *
         */
        Player(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer);
        /**
         * @brief Set movement direction of player
         *
         * @param direction - movement direction
         */
        void setMovementDirection(MovementDirection direction);
        /**
         * @brief Update movement and animation of player
         *
         * @param delta - time in milliseconds
         */
        virtual void update(const unsigned int delta) override;

      private:
        /**
         * @brief Is movement direction by Y
         *
         */
        bool isMovingVertically() const;
        /**
         * @brief Is movement direction by X
         *
         */
        bool isMovingHorizontally() const;

        MovementDirection movementDirection = MovementDirection::None; // movement direction
        const float speed = 0.2f;                                      // speed
        std::shared_ptr<Animation> movement;                           // movement animation
    };
} // namespace bomberman

#endif // _BOMBERMAN_ENTITIES_PLAYER_H_

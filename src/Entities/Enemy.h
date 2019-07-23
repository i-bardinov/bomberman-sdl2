#ifndef _BOMBERMAN_ENTITIES_ENEMY_H_
#define _BOMBERMAN_ENTITIES_ENEMY_H_

#include <utility>

#include "Entities/Creature.h"

namespace bomberman
{
    /**
     * @brief AI types for enemies
     *
     */
    enum class AIType : int
    {
        Wandering,
        Chasing
    };
    /**
     * @brief Enemy class
     *
     */
    class Enemy : public Creature
    {
      public:
        /**
         * @brief Inherit constructor
         *
         */
        using Creature::Creature;
        /**
         * @brief Move enemy to specified position
         *
         * @param x - position X
         * @param y - position Y
         */
        void moveTo(const int x, const int y);
        /**
         * @brief Move enemy for specified diff of cells
         *
         * @param pathToCell - pair of number of cells on X and Y
         */
        void moveToCell(std::pair<int, int> pathToCell);
        /**
         * @brief Return is enemy moving to cell or not
         *
         * @return true - moving to cell
         * @return false - not moving to cell
         */
        bool isMovingToCell() const;
        /**
         * @brief Can enemy attack
         *
         * @return true - enemy can attack player
         * @return false - can't attack
         */
        bool canAttack() const;
        /**
         * @brief Get the Attack Radius of enemy
         *
         * @return int - attack radius
         */
        int getAttackRadius() const;
        /**
         * @brief Set AI type
         *
         * @param type - AI type
         */
        void setAIType(AIType type);
        /**
         * @brief Update movement of enemy
         *
         * @param delta - time in milliseconds
         */
        virtual void update(const unsigned int delta) override;
        /**
         * @brief Generate new path if enemy finish movement
         *
         */
        void generateNewPath();

      private:
        /**
         * @brief update movement of enemy
         *
         * @param delta - time in milliseconds
         */
        void updateMovement(const unsigned int delta);

        // movement
        int newPositionX = 0;      // position X to move
        int newPositionY = 0;      // position Y to move
        bool movingToCell = false; // is moving to cell
        std::pair<int, int> path;  // diff of cells to move
        // AI
        AIType aiType = AIType::Wandering; // AI type
        // consts
        const float baseSpeed = 0.07f; // speed of enemy
        const int attackRadius = 5;    // attack radius (in cells)
    };
} // namespace bomberman

#endif // _BOMBERMAN_ENTITIES_ENEMY_H_

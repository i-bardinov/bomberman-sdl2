#include <chrono>
#include <random>

#include "Entities/Enemy.h"

namespace bomberman
{
    void Enemy::moveTo(const int x, const int y)
    {
        // start a moving, see update func
        setMoving(true);
        // save new position
        newPositionX = getPositionX() + x;
        newPositionY = getPositionY() + y;
    }

    void Enemy::moveToCell(std::pair<int, int> pathToCell)
    {
        // save moving path
        path = pathToCell;
        movingToCell = true;
        // move enemy to nearest cell
        newPositionX = getPositionX() - ((getPositionX() - newPositionX) % getWidth());
        newPositionY = getPositionY() - ((getPositionY() - newPositionY) % getHeight());
    }

    bool Enemy::isMovingToCell() const
    {
        return movingToCell;
    }

    bool Enemy::canAttack() const
    {
        return aiType == AIType::Chasing;
    }

    int Enemy::getAttackRadius() const
    {
        return attackRadius * getWidth();
    }

    void Enemy::setAIType(AIType type)
    {
        aiType = type;
    }

    void Enemy::update(const unsigned int delta)
    {
        Creature::update(delta);
        // simple wandering moving
        if(isMoving())
        {
            updateMovement(delta);
        }
        // moving to cell
        else if(movingToCell)
        {
            moveTo(path.second * getWidth(), path.first * getHeight());
        }
        // new random path
        else
        {
            generateNewPath();
        }
    }

    void Enemy::updateMovement(const unsigned int delta)
    {
        // calculate consts for movement
        const int newPositionDiffX = getPositionX() - newPositionX;
        const int newPositionDiffY = getPositionY() - newPositionY;
        const char signOfX = (newPositionDiffX > 0) ? 1 : ((newPositionDiffX < 0) ? -1 : 0);
        const char signOfY = (newPositionDiffY > 0) ? 1 : ((newPositionDiffY < 0) ? -1 : 0);
        const float posDiff = static_cast<int>(floor(baseSpeed * delta));

        prevPosDeltaX = posDiff * -signOfX;
        prevPosDeltaY = posDiff * -signOfY;

        // finish movement
        if(newPositionDiffX * signOfX <= posDiff && newPositionDiffY * signOfY <= posDiff)
        {
            setMoving(false);
            movingToCell = false;
            setPosition(newPositionX, newPositionY);
            return;
        }
        // move sprite to next tick pos
        setPosition(getPositionX() - floor(posDiff) * signOfX, getPositionY() - floor(posDiff) * signOfY);
    }

    void Enemy::generateNewPath()
    {
        // create random func
        const auto seed = std::chrono::high_resolution_clock::now().time_since_epoch().count();
        auto randPath = std::bind(std::uniform_int_distribution<int>(1, 10),
                                  std::mt19937(static_cast<unsigned int>(seed)));
        auto randSign = std::bind(std::uniform_int_distribution<int>(-1, 1),
                                  std::mt19937(static_cast<unsigned int>(seed)));

        // generate direction and cells
        const int randUpDown = randPath();
        const int randUpDownSign = randSign();
        if(randUpDownSign != 0)
        {
            moveTo(0, randUpDown * randUpDownSign * getHeight());
            return;
        }
        const int randLeftRight = randPath();
        const int randLeftRightSign = randSign();
        if(randLeftRightSign != 0)
        {
            moveTo(randLeftRight * randLeftRightSign * getWidth(), 0);
        }
    }
} // namespace bomberman

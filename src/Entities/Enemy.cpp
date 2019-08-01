#include <chrono>
#include <functional>
#include <random>

#include "Const.h"
#include "Entities/Enemy.h"

namespace bomberman
{
    Enemy::Enemy(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer)
        : Creature(_texture, _renderer)
    {
        // movement animation
        movement = std::make_shared<Animation>();
        movement->addAnimationEntity(AnimationEntity(0, 0, tileSize, tileSize));
        movement->addAnimationEntity(AnimationEntity(tileSize * 1, 0, tileSize, tileSize));
        movement->addAnimationEntity(AnimationEntity(tileSize * 2, 0, tileSize, tileSize));
        movement->addAnimationEntity(AnimationEntity(tileSize * 3, 0, tileSize, tileSize));
        movement->addAnimationEntity(AnimationEntity(tileSize * 4, 0, tileSize, tileSize));
        movement->addAnimationEntity(AnimationEntity(tileSize * 5, 0, tileSize, tileSize));
        movement->addAnimationEntity(AnimationEntity(tileSize * 6, 0, tileSize, tileSize));
        movement->addAnimationEntity(AnimationEntity(tileSize * 7, 0, tileSize, tileSize));
        movement->setSprite(this);
        addAnimation(movement);
    }

    void Enemy::moveTo(const int x, const int y)
    {
        // start a moving, see update func
        movement->play();
        setMoving(true);
        // save new position
        newPositionX = getPositionX() + x;
        newPositionY = getPositionY() + y;
        // flip
        if(x < 0)
        {
            setFlip(SDL_FLIP_HORIZONTAL);
        }
        else if(x > 0)
        {
            setFlip(SDL_FLIP_NONE);
        }
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
        const int posDiff = static_cast<int>(floor((canAttack() ? attackSpeed : baseSpeed) * delta * getWidth()));

        prevPosDeltaX = posDiff * -signOfX;
        prevPosDeltaY = posDiff * -signOfY;

        // finish movement
        if(newPositionDiffX * signOfX <= posDiff && newPositionDiffY * signOfY <= posDiff)
        {
            movement->pause();
            setMoving(false);
            movingToCell = false;
            setPosition(newPositionX, newPositionY);
            return;
        }
        // move sprite to next tick pos
        setPosition(getPositionX() - static_cast<int>(floor(posDiff)) * signOfX,
                    getPositionY() - static_cast<int>(floor(posDiff)) * signOfY);
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

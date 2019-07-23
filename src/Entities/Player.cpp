#include "Player.h"
#include "Const.h"

namespace bomberman
{
    Player::Player(std::shared_ptr<SDL_Texture> texture, SDL_Renderer* renderer) : Creature(texture, renderer)
    {
        // animation left
        moveLeft = std::make_shared<Animation>();
        moveLeft->addAnimationEntity(AnimationEntity(0, 0, tileSize, tileSize));
        moveLeft->addAnimationEntity(AnimationEntity(tileSize, 0, tileSize, tileSize));
        moveLeft->addAnimationEntity(AnimationEntity(tileSize * 2, 0, tileSize, tileSize));
        moveLeft->setSprite(this);
        addAnimation(moveLeft);
        // animation right
        moveRight = std::make_shared<Animation>();
        moveRight->addAnimationEntity(AnimationEntity(0, tileSize, tileSize, tileSize));
        moveRight->addAnimationEntity(AnimationEntity(tileSize, tileSize, tileSize, tileSize));
        moveRight->addAnimationEntity(AnimationEntity(tileSize * 2, tileSize, tileSize, tileSize));
        moveRight->setSprite(this);
        addAnimation(moveRight);
        // animation down
        moveDown = std::make_shared<Animation>();
        moveDown->addAnimationEntity(AnimationEntity(tileSize * 3, 0, tileSize, tileSize));
        moveDown->addAnimationEntity(AnimationEntity(tileSize * 4, 0, tileSize, tileSize));
        moveDown->addAnimationEntity(AnimationEntity(tileSize * 5, 0, tileSize, tileSize));
        moveDown->setSprite(this);
        addAnimation(moveDown);
        // animation up
        moveUp = std::make_shared<Animation>();
        moveUp->addAnimationEntity(AnimationEntity(tileSize * 3, tileSize, tileSize, tileSize));
        moveUp->addAnimationEntity(AnimationEntity(tileSize * 4, tileSize, tileSize, tileSize));
        moveUp->addAnimationEntity(AnimationEntity(tileSize * 5, tileSize, tileSize, tileSize));
        moveUp->setSprite(this);
        addAnimation(moveUp);
    }

    void Player::setMovementDirection(MovementDirection direction)
    {
        movementDirection = direction;
        setMoving(movementDirection != MovementDirection::None);
        moveLeft->reset();
        moveRight->reset();
        moveUp->reset();
        moveDown->reset();
        switch(movementDirection)
        {
            case MovementDirection::Left:
                moveLeft->play();
                break;
            case MovementDirection::Right:
                moveRight->play();
                break;
            case MovementDirection::Up:
                moveUp->play();
                break;
            case MovementDirection::Down:
                moveDown->play();
                break;
            default:
                break;
        }
    }

    void Player::update(const unsigned int delta)
    {
        // movement
        if(isMoving())
        {
            const int posDiff = static_cast<int>(floor(speed * delta));
            prevPosDeltaX =
                posDiff *
                (isMovingHorizontally() ? (movementDirection == MovementDirection::Left ? -1 : 1) : 0);
            prevPosDeltaY =
                posDiff * (isMovingVertically() ? (movementDirection == MovementDirection::Up ? -1 : 1) : 0);
            // move sprite to next tick pos
            setPosition(getPositionX() + prevPosDeltaX, getPositionY() + prevPosDeltaY);
        }

        Creature::update(delta);
    }

    bool Player::isMovingVertically() const
    {
        return movementDirection == MovementDirection::Up || movementDirection == MovementDirection::Down;
    }

    bool Player::isMovingHorizontally() const
    {
        return movementDirection == MovementDirection::Left || movementDirection == MovementDirection::Right;
    }
} // namespace bomberman

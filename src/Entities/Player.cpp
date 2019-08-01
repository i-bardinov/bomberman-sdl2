#include "Player.h"
#include "Const.h"

namespace bomberman
{
    Player::Player(std::shared_ptr<SDL_Texture> _texture, SDL_Renderer* _renderer)
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

    void Player::setMovementDirection(MovementDirection direction)
    {
        movementDirection = direction;
        setMoving(movementDirection != MovementDirection::None);
        movement->play();
        switch(movementDirection)
        {
            case MovementDirection::Left:
                setFlip(SDL_FLIP_HORIZONTAL);
                break;
            case MovementDirection::Right:
                setFlip(SDL_FLIP_NONE);
                break;
            case MovementDirection::None:
                movement->pause();
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
            const int posDiff = static_cast<int>(floor(speed * delta * getWidth()));
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

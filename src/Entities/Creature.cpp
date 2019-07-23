#include "Entities/Creature.h"

namespace bomberman
{
    void Creature::revertLastMove()
    {
        setPosition(getPositionX() - prevPosDeltaX, getPositionY() - prevPosDeltaY);
    }

    void Creature::setMoving(bool _moving)
    {
        this->moving = _moving;
    }

    bool Creature::isMoving() const
    {
        return moving;
    }
} // namespace bomberman

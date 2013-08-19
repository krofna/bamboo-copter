#ifndef WORLD_OBJECT_HPP
#define WORLD_OBJECT_HPP

#include "Shared/Rectangle.hpp"

class WorldObject
{
public:
    Rectangle GetRect() const;

private:
    Rectangle Rect;
};

#endif

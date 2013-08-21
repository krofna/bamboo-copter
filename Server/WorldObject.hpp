#ifndef WORLD_OBJECT_HPP
#define WORLD_OBJECT_HPP

#include "Shared/Rectangle.hpp"
#include "Shared/BasicTypes.hpp"

class WorldObject
{
public:
    WorldObject(uint64 GUID, uint32 Entry, uint32 x, uint32 y);

    Rectangle<uint32> GetRect() const;
    virtual void Update();

private:
    uint64 GUID;
    uint32 Entry;
    Rectangle<uint32> Rect;
};

#endif

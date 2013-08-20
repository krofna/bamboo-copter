#include "WorldObject.hpp"

WorldObject::WorldObject(uint64 GUID, uint32 Entry, uint32 x, uint32 y) :
GUID(GUID),
Entry(Entry),
Rect(sf::Vector2<uint32>(x, y), sf::Vector2<uint32>(0, 0)) // TODO: Size from Entry/Template
{
}

Rectangle<uint32> WorldObject::GetRect() const
{
    return Rect;
}

void WorldObject::Update()
{
}

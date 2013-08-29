#include "Object.hpp"

uint16 Object::GetX() const
{
    return Rectg.left;
}

uint16 Object::GetY() const
{
    return Rectg.top;
}

sf::Vector2<uint16> Object::Position() const
{
    return Rectg.NW();
}

#ifndef OBJECT_HPP
#define OBJECT_HPP

#include "Shared/Rectangle.hpp"
#include "Shared/BasicTypes.hpp"

class Object
{
public:
    void SetRect(Rect<uint16> NewRect);
    Rect<uint16> GetRect() const;
    uint16 GetX() const;
    uint16 GetY() const;
    sf::Vector2<uint16> Position() const;

protected:
    Rect<uint16> Rectg;
};

#endif

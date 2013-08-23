#include "WorldObject.hpp"

Node::Node()
{
    Reset();
}

void Node::Reset()
{
    Color = 0;
}

uint16 Node::GetX() const
{
    return ((WorldObject*)this)->GetRect().left;
}

uint16 Node::GetY() const
{
    return ((WorldObject*)this)->GetRect().top;
}

sf::Vector2<uint16> Node::Position() const
{
    return ((WorldObject*)this)->GetRect().NW();
}

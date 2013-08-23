#ifndef NODE_HPP
#define NODE_HPP

class Node
{
    friend class Pathfinder;
    friend class NodeQueue;
public:
    Node();
    void Reset();
    uint16 GetX() const;
    uint16 GetY() const;
    sf::Vector2<uint16> Position() const;

private:
    Node* pParent;
    uint16 Cost;
    uint16 Color;
    size_t i;
};

#endif

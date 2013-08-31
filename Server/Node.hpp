#ifndef NODE_HPP
#define NODE_HPP

#include "Object.hpp"
#include "Shared/LinkedList.hpp"

class WorldObject;
class Player;

// Represents a terrain
class Node : public Object, public LinkedList<WorldObject>
{
    friend class Pathfinder;
    friend class NodeQueue;
public:
    Node();
    void Reset();
    void Remove(WorldObject* pObject);

private:
    Node* pParent;
    uint16 Cost;
    uint16 Color; // uint32?? TODO
    size_t i;
};

#endif

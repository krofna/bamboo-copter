#include "Node.hpp"

Node::Node()
{
    Reset();
}

void Node::Reset()
{
    Color = 0;
}

void Node::Remove(WorldObject* pObject)
{
    for (LinkedList* pIter = this; pIter; pIter = pIter->Next())
        if (pIter->Data() == pObject)
            pIter->Unlink();
}

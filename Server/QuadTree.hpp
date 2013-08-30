#ifndef QUAD_TREE_HPP
#define QUAD_TREE_HPP

#include "Shared/Rectangle.hpp"
#include "Shared/LinkedList.hpp"
#include "Shared/BasicTypes.hpp"
#include "Node.hpp"
#include <limits>
#include <memory>

class WorldObject;

class QuadTree : private LinkedList<Node>
{
public:
    QuadTree();
    QuadTree(Rect<uint16> Area, QuadTree* pParent);
    ~QuadTree();

    bool Insert(WorldObject* pObject);
    bool Remove(WorldObject* pObject);
    void Update(WorldObject* pObject);

    template <class T>
    void Traverse(T Func);

    template <class T>
    void TraverseArea(Rect<uint16> Area, T Func);

    Node* At(Rect<uint16> Area);
    bool CreateNode(Node* pArea);
    Node* Locate(WorldObject* pObject);

private:
    Rect<uint16> Area;
    QuadTree* pParent;
    QuadTree* NW;
    QuadTree* NE;
    QuadTree* SW;
    QuadTree* SE;
};

template <class T>
void QuadTree::Traverse(T Func)
{
    if (pParent)
        for (LinkedList* pIter = this; pIter; pIter = pIter->Next())
            for (LinkedList<WorldObject>* pNest = pIter->Data(); pNest; pNest = pNest->Next())
                Func(pNest->Data());

    if (!NW)
        return;

    NW->Traverse(Func);
    NE->Traverse(Func);
    SW->Traverse(Func);
    SE->Traverse(Func);
}

template <class T>
void QuadTree::TraverseArea(Rect<uint16> Area, T Func)
{
    if (pParent)
        if (this->Area.intersects(Area))
            for (LinkedList* pIter = this; pIter; pIter = pIter->Next())
                for (LinkedList<WorldObject>* pNest = pIter->Data(); pNest; pNest = pNest->Next())
                    Func(pNest->Data());

    if (!NW)
        return;

    NW->TraverseArea(Area, Func);
    NE->TraverseArea(Area, Func);
    SW->TraverseArea(Area, Func);
    SE->TraverseArea(Area, Func);
}

#endif

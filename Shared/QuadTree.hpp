#ifndef QUAD_TREE_HPP
#define QUAD_TREE_HPP

#include "Shared/Rectangle.hpp"
#include "Shared/LinkedList.hpp"
#include "Shared/BasicTypes.hpp"
#include "WorldObject.hpp"

class QuadTree : private LinkedList<WorldObject>
{
public:
    QuadTree(Rectangle Area, QuadTree* pParent);
    ~QuadTree();

    bool Insert(WorldObject* pObject);
    void Remove(WorldObject* pObject);
    void Update(WorldObject* pObject);

protected:
    template <class T>
    void Traverse(T Func);

    template <class T>
    void TraverseArea(Rectangle Area, T Func);

    template <class T>
    void Foreach(T Func);

private:
    QuadTree* Locate(WorldObject* pObject);

    uint8 Size;
    Rectangle Area;

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
        Foreach(Func);

    if (!NW)
        return;

    NW->Traverse(Func);
    NE->Traverse(Func);
    SW->Traverse(Func);
    SE->Traverse(Func);
}

template <class T>
void QuadTree::TraverseArea(Rectangle Area, T Func)
{
    if (pParent)
    {
        if (!this->Area.intersects(Area))
            return;

        Foreach(Func);
    }

    if (!NW)
        return;

    NW->TraverseArea(Area, Func);
    NE->TraverseArea(Area, Func);
    SW->TraverseArea(Area, Func);
    SE->TraverseArea(Area, Func);
}

template <class T>
void QuadTree::Foreach(T Func)
{
    for (LinkedList* pIter = this; pIter != nullptr; pIter = pIter->Next())
        if (WorldObject* pObject = pIter->Data())
            Func(pObject);
}

#endif

#ifndef QUAD_TREE_HPP
#define QUAD_TREE_HPP

#include "Shared/Rectangle.hpp"
#include "Shared/LinkedList.hpp"
#include "Shared/BasicTypes.hpp"
#include <limits>
#include <memory>

static const uint32 MAX_QUAD_CAPACITY = 16;

template <class W, class U>
class QuadTree : private LinkedList<W>
{
public:
    QuadTree();
    QuadTree(Rect<U> Area, QuadTree* pParent);
    ~QuadTree();

    bool Insert(W* pObject);
    void Remove(W* pObject);
    void Update(W* pObject);

    template <class T>
    void Traverse(T Func);

    template <class T>
    void TraverseArea(Rect<U> Area, T Func);

    template <class T>
    void Foreach(T Func);

private:
    QuadTree* Locate(W* pObject);

    uint8 Size;
    Rect<U> Area;

    QuadTree* pParent;
    QuadTree* NW;
    QuadTree* NE;
    QuadTree* SW;
    QuadTree* SE;
};

#include "QuadTree.inl"

#endif

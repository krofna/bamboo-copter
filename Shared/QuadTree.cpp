#include "Shared/QuadTree.hpp"

#include <memory>

static const uint32 MAX_QUAD_CAPACITY = 32;

QuadTree::QuadTree(Rectangle Area, QuadTree* pParent) :
LinkedList(nullptr, nullptr),
Size(0),
Area(Area),
pParent(pParent),
NW(nullptr),
NE(nullptr),
SW(nullptr),
SE(nullptr)
{
}

QuadTree::~QuadTree()
{
    Traverse(std::default_delete<WorldObject>());
}

bool QuadTree::Insert(WorldObject* pObject)
{
    if (pParent)
    {
        if (!Area.intersects(pObject->GetRect()))
            return false;

        if (Size < MAX_QUAD_CAPACITY)
        {
            LinkedList::Insert(pObject);
            ++Size;
            return true;
        }
    }

    if (!NW)
    {
        NW = new QuadTree(Rectangle(Area.NW(), Area.Size() / 2.f), this);
        NE = new QuadTree(Rectangle(Area.NW() + sf::Vector2f(Area.Size().x / 2.f, 0.f), Area.Size() / 2.f), this);
        SW = new QuadTree(Rectangle(Area.NW() + sf::Vector2f(0.f, Area.Size().y / 2.f), Area.Size() / 2.f), this);
        SE = new QuadTree(Rectangle(Area.Size() / 2.f, Area.Size() / 2.f), this);
    }

    if (NW->Insert(pObject)) return true;
    if (NE->Insert(pObject)) return true;
    if (SW->Insert(pObject)) return true;
    if (SE->Insert(pObject)) return true;

    return false;
}

void QuadTree::Remove(WorldObject* pObject)
{
    QuadTree* pTree = Locate(pObject);

    for (LinkedList* pIter = pTree; pIter != nullptr; pIter = pIter->Next())
    {
        if (pIter->Data() == pObject)
        {
            pIter->Unlink();
            --Size;
            return;
        }
    }
}

QuadTree* QuadTree::Locate(WorldObject* pObject)
{
    QuadTree* pTree;

    if (pParent)
    {
        if (!Area.intersects(pObject->GetRect()))
            return nullptr;

        for (LinkedList* pIter = this; pIter != nullptr; pIter = pIter->Next())
            if (pIter->Data() == pObject)
                return this;
    }

    if ((pTree = NW->Locate(pObject))) return pTree;
    if ((pTree = NE->Locate(pObject))) return pTree;
    if ((pTree = SW->Locate(pObject))) return pTree;
    if ((pTree = SE->Locate(pObject))) return pTree;

    return nullptr;
}

void QuadTree::Update(WorldObject* pObject)
{
    QuadTree* pTree = Locate(pObject);
    if (pTree && !pTree->Area.intersects(pObject->GetRect()))
    {
        pTree->Remove(pObject);
        Insert(pObject);
    }
}

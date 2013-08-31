#include "WorldObject.hpp"
#include "QuadTree.hpp"
#include "Shared/Log.hpp"

QuadTree::QuadTree() :
QuadTree(Rect<uint16>(sf::Vector2<uint16>(0, 0), sf::Vector2<uint16>(std::numeric_limits<uint16>::max(), std::numeric_limits<uint16>::max())))
{
}

QuadTree::QuadTree(Rect<uint16> Area) :
Area(Area),
NW(nullptr),
NE(nullptr),
SW(nullptr),
SE(nullptr),
pNode(nullptr)
{
}

QuadTree::~QuadTree()
{
    Traverse(std::default_delete<WorldObject>());
    TraverseNodes(std::default_delete<Node>());
}

bool QuadTree::Insert(WorldObject* pObject)
{
    if (pNode && pNode->GetRect().contains(pObject->GetRect()))
    {
        pNode->Insert(pObject);
        return true;
    }

    if (NW->Insert(pObject)) return true;
    if (NE->Insert(pObject)) return true;
    if (SW->Insert(pObject)) return true;
    if (SE->Insert(pObject)) return true;
    return false;
}

bool QuadTree::Remove(WorldObject* pObject)
{
    if (pNode && pNode->GetRect().contains(pObject->GetRect()))
    {
        for (LinkedList<WorldObject>* pNest = pNode; pNest != nullptr; pNest = pNest->Next())
        {
            if (pNest->Data() == pObject)
            {
                pNest->Unlink();
                return true;
            }
        }
        sLog.Write(LOG_ERROR, "Object is not where it should be! GUID: %llu", pObject->GetGUID());
        return true;
    }

    if (NW->Locate(pObject)) return true;
    if (NE->Locate(pObject)) return true;
    if (SW->Locate(pObject)) return true;
    if (SE->Locate(pObject)) return true;
    return false;
}

Node* QuadTree::Locate(WorldObject* pObject)
{
    Node* pTree;

    if (pNode->GetRect().contains(pObject->GetRect()))
    {
        for (LinkedList<WorldObject>* pNest = pNode; pNest != nullptr; pNest = pNest->Next())
            if (pNest->Data() == pObject)
                return pNode;

        sLog.Write(LOG_ERROR, "Object is not where it should be! GUID: %llu", pObject->GetGUID());
        return pNode; // return regardless of error, required for Update to work
    }

    if ((pTree = NW->Locate(pObject))) return pTree;
    if ((pTree = NE->Locate(pObject))) return pTree;
    if ((pTree = SW->Locate(pObject))) return pTree;
    if ((pTree = SE->Locate(pObject))) return pTree;

    sLog.Write(LOG_ERROR, "Object is outside of terrain! GUID: %llu", pObject->GetGUID());
    return nullptr;
}

void QuadTree::Update(WorldObject* pObject)
{
    Node* pNode = Locate(pObject);
    if (pNode && !pNode->GetRect().contains(pObject->GetRect()))
    {
        pNode->Remove(pObject);
        Insert(pObject);
    }
}

Node* QuadTree::At(Rect<uint16> Area)
{
    if (this->Area.contains(Area))
        if (pNode->GetRect().contains(Area))
            return pNode;

    if (!NW)
    {
        sLog.Write(LOG_ERROR, "Requested node at unaligned area: %u %u %u %u", Area.left, Area.top, Area.width, Area.height);
        return nullptr;
    }

    if (Node* pNode = NW->At(Area)) return pNode;
    if (Node* pNode = NE->At(Area)) return pNode;
    if (Node* pNode = SW->At(Area)) return pNode;
    if (Node* pNode = SE->At(Area)) return pNode;
    return nullptr;
}

bool QuadTree::CreateNode(Node* pArea)
{
    if (!pNode && Area.intersects(pArea->GetRect()))
    {
        pNode = pArea;
        return true;
    }

    if (!NW)
    {
        sf::Vector2<uint16> HalfArea = Area.Size() / uint16(2);
        NW = new QuadTree(Rect<uint16>(Area.NW(), HalfArea));
        NE = new QuadTree(Rect<uint16>(Area.NW() + sf::Vector2<uint16>(Area.Size().x / 2, 0), HalfArea));
        SW = new QuadTree(Rect<uint16>(Area.NW() + sf::Vector2<uint16>(0, Area.Size().y / 2), HalfArea));
        SE = new QuadTree(Rect<uint16>(HalfArea, HalfArea));
    }

    if (NW->CreateNode(pArea)) return true;
    if (NE->CreateNode(pArea)) return true;
    if (SW->CreateNode(pArea)) return true;
    if (SE->CreateNode(pArea)) return true;

    sLog.Write(LOG_ERROR, "Impossible to create area! This should never happen");
    return false;
}

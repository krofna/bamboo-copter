#include "WorldObject.hpp"
#include "QuadTree.hpp"
#include "Shared/Log.hpp"

QuadTree::QuadTree() :
QuadTree(Rect<uint16>(sf::Vector2<uint16>(0, 0), sf::Vector2<uint16>(std::numeric_limits<uint16>::max(), std::numeric_limits<uint16>::max())), nullptr)
{
}

QuadTree::QuadTree(Rect<uint16> Area, QuadTree* pParent) :
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

        for (LinkedList* pIter = this; pIter != nullptr; pIter = pIter->Next())
        {
            if (pIter->Data()->GetRect().intersects(pObject->GetRect()))
            {
                pIter->Data()->Insert(pObject);
                return true;
            }
        }
        sLog.Write(LOG_ERROR, "Unaligned object! GUID: %llu", pObject->GetGUID());
        return false;
    }

    if (!NW)
    {
        sLog.Write(LOG_ERROR, "Object outside of terrain! GUID: %llu", pObject->GetGUID());
        return false;
    }

    if (NW->Insert(pObject)) return true;
    if (NE->Insert(pObject)) return true;
    if (SW->Insert(pObject)) return true;
    if (SE->Insert(pObject)) return true;
    return false;
}

bool QuadTree::Remove(WorldObject* pObject)
{
    if (pParent)
    {
        if (!Area.intersects(pObject->GetRect()))
            return false;

        for (LinkedList* pIter = this; pIter != nullptr; pIter = pIter->Next())
        {
            for (LinkedList<WorldObject>* pNest = pIter->Data(); pNest != nullptr; pNest = pNest->Next())
            {
                if (pNest->Data() == pObject)
                {
                    pNest->Unlink();
                    return true;
                }
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

    if (pParent)
    {
        if (!Area.intersects(pObject->GetRect()))
            return nullptr;

        for (LinkedList* pIter = this; pIter != nullptr; pIter = pIter->Next())
            for (LinkedList<WorldObject>* pNest = pIter->Data(); pNest != nullptr; pNest = pNest->Next())
                if (pNest->Data() == pObject)
                    return pIter->Data();
    }

    if ((pTree = NW->Locate(pObject))) return pTree;
    if ((pTree = NE->Locate(pObject))) return pTree;
    if ((pTree = SW->Locate(pObject))) return pTree;
    if ((pTree = SE->Locate(pObject))) return pTree;
    return nullptr;
}

void QuadTree::Update(WorldObject* pObject)
{
    Node* pNode = Locate(pObject);
    if (pNode && !pNode->GetRect().intersects(pObject->GetRect()))
    {
        pNode->Remove(pObject);
        Insert(pObject);
    }
}

Node* QuadTree::At(Rect<uint16> Area)
{
    if (pParent)
    {
        if (!this->Area.intersects(Area))
            return nullptr;

        for (LinkedList* pIter = this; pIter != nullptr; pIter = pIter->Next())
            if (pIter->Data()->GetRect() == Area)
                return pIter->Data();

        sLog.Write(LOG_ERROR, "Requested node at unaligned area!");
        return nullptr;
    }

    if (!NW)
        return nullptr;

    if (Node* pNode = NW->At(Area)) return pNode;
    if (Node* pNode = NE->At(Area)) return pNode;
    if (Node* pNode = SW->At(Area)) return pNode;
    if (Node* pNode = SE->At(Area)) return pNode;
    return nullptr;
}

bool QuadTree::CreateNode(Node* pArea)
{
    if (pParent)
    {
        if (!Area.intersects(pArea->GetRect()))
            return false;

        LinkedList::Insert(pArea);
        return true;
    }

    if (!NW)
    {
        sf::Vector2<uint16> HalfArea = Area.Size() / uint16(2);
        NW = new QuadTree(Rect<uint16>(Area.NW(), HalfArea), this);
        NE = new QuadTree(Rect<uint16>(Area.NW() + sf::Vector2<uint16>(Area.Size().x / 2, 0), HalfArea), this);
        SW = new QuadTree(Rect<uint16>(Area.NW() + sf::Vector2<uint16>(0, Area.Size().y / 2), HalfArea), this);
        SE = new QuadTree(Rect<uint16>(HalfArea, HalfArea), this);
    }

    if (NW->CreateNode(pArea)) return true;
    if (NE->CreateNode(pArea)) return true;
    if (SW->CreateNode(pArea)) return true;
    if (SE->CreateNode(pArea)) return true;

    sLog.Write(LOG_ERROR, "Impossible to create area! This should never happen");
    return false;
}

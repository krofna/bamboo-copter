template <class U> template <class T>
void QuadTree<U>::Traverse(T Func)
{
    if (pParent)
        LinkedList::Foreach(Func);

    if (!NW)
        return;

    NW->Traverse(Func);
    NE->Traverse(Func);
    SW->Traverse(Func);
    SE->Traverse(Func);
}

template <class U> template <class T>
void QuadTree<U>::TraverseArea(Rect<U> Area, T Func)
{
    if (pParent)
    {
        if (!this->Area.intersects(Area))
            return;

        LinkedList::Foreach(Func);
    }

    if (!NW)
        return;

    NW->TraverseArea(Area, Func);
    NE->TraverseArea(Area, Func);
    SW->TraverseArea(Area, Func);
    SE->TraverseArea(Area, Func);
}

template <class U>
QuadTree<U>::QuadTree() :
QuadTree(Rect<U>(sf::Vector2<U>(0, 0), sf::Vector2<U>(std::numeric_limits<uint32>::max(), std::numeric_limits<uint32>::max())), nullptr)
{
}

template <class U>
QuadTree<U>::QuadTree(Rect<U> Area, QuadTree* pParent) :
Size(0),
Area(Area),
pParent(pParent),
NW(nullptr),
NE(nullptr),
SW(nullptr),
SE(nullptr)
{
}

template <class U>
QuadTree<U>::~QuadTree()
{
    Traverse(std::default_delete<WorldObject>());
}

template <class U>
bool QuadTree<U>::Insert(WorldObject* pObject)
{
    if (pParent)
    {
        if (!Area.intersects(pObject->GetRect()))
            return false;

        if (this->Size < MAX_QUAD_CAPACITY)
        {
            LinkedList::Insert(pObject);
            ++Size;
            return true;
        }
    }

    if (!NW)
    {
        this->NW = new QuadTree(Rect<U>(Area.NW(), Area.Size() / static_cast<U>(2)), this);
        this->NE = new QuadTree(Rect<U>(Area.NW() + sf::Vector2<U>(Area.Size().x / static_cast<U>(2), static_cast<U>(0)), Area.Size() / static_cast<U>(2)), this);
        this->SW = new QuadTree(Rect<U>(Area.NW() + sf::Vector2<U>(static_cast<U>(0), Area.Size().y / static_cast<U>(2)), Area.Size() / static_cast<U>(2)), this);
        this->SE = new QuadTree(Rect<U>(Area.Size() / static_cast<U>(2), Area.Size() / static_cast<U>(2)), this);
    }

    if (this->NW->Insert(pObject)) return true;
    if (this->NE->Insert(pObject)) return true;
    if (this->SW->Insert(pObject)) return true;
    if (this->SE->Insert(pObject)) return true;

    return false;
}

template <class U>
void QuadTree<U>::Remove(WorldObject* pObject)
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

template <class U>
QuadTree<U>* QuadTree<U>::Locate(WorldObject* pObject)
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

template <class U>
void QuadTree<U>::Update(WorldObject* pObject)
{
    QuadTree* pTree = Locate(pObject);
    if (pTree && !pTree->Area.intersects(pObject->GetRect()))
    {
        pTree->Remove(pObject);
        Insert(pObject);
    }
}

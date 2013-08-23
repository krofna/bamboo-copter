template <class W, class U> template <class T>
void QuadTree<W, U>::Traverse(T Func)
{
    if (pParent)
        LinkedList<W>::Foreach(Func);

    if (!NW)
        return;

    NW->Traverse(Func);
    NE->Traverse(Func);
    SW->Traverse(Func);
    SE->Traverse(Func);
}

template <class W, class U> template <class T>
void QuadTree<W, U>::TraverseArea(Rect<U> Area, T Func)
{
    if (pParent)
    {
        if (!this->Area.intersects(Area))
            return;

        LinkedList<W>::Foreach(Func);
    }

    if (!NW)
        return;

    NW->TraverseArea(Area, Func);
    NE->TraverseArea(Area, Func);
    SW->TraverseArea(Area, Func);
    SE->TraverseArea(Area, Func);
}

template <class W, class U>
QuadTree<W, U>::QuadTree() :
QuadTree(Rect<U>(sf::Vector2<U>(0, 0), sf::Vector2<U>(std::numeric_limits<uint32>::max(), std::numeric_limits<uint32>::max())), nullptr)
{
}

template <class W, class U>
QuadTree<W, U>::QuadTree(Rect<U> Area, QuadTree* pParent) :
Size(0),
Area(Area),
pParent(pParent),
NW(nullptr),
NE(nullptr),
SW(nullptr),
SE(nullptr)
{
}

template <class W, class U>
QuadTree<W, U>::~QuadTree()
{
    Traverse(std::default_delete<W>());
}

template <class W, class U>
bool QuadTree<W, U>::Insert(W* pObject)
{
    if (pParent)
    {
        if (!Area.intersects(pObject->GetRect()))
            return false;

        if (this->Size < MAX_QUAD_CAPACITY)
        {
            LinkedList<W>::Insert(pObject);
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

template <class W, class U>
void QuadTree<W, U>::Remove(W* pObject)
{
    QuadTree* pTree = Locate(pObject);

    for (LinkedList<W>* pIter = pTree; pIter != nullptr; pIter = pIter->Next())
    {
        if (pIter->Data() == pObject)
        {
            pIter->Unlink();
            --Size;
            return;
        }
    }
}

template <class W, class U>
QuadTree<W, U>* QuadTree<W, U>::Locate(W* pObject)
{
    QuadTree* pTree;

    if (pParent)
    {
        if (!Area.intersects(pObject->GetRect()))
            return nullptr;

        for (LinkedList<W>* pIter = this; pIter != nullptr; pIter = pIter->Next())
            if (pIter->Data() == pObject)
                return this;
    }

    if ((pTree = NW->Locate(pObject))) return pTree;
    if ((pTree = NE->Locate(pObject))) return pTree;
    if ((pTree = SW->Locate(pObject))) return pTree;
    if ((pTree = SE->Locate(pObject))) return pTree;

    return nullptr;
}

template <class W, class U>
void QuadTree<W, U>::Update(W* pObject)
{
    QuadTree* pTree = Locate(pObject);
    if (pTree && !pTree->Area.intersects(pObject->GetRect()))
    {
        pTree->Remove(pObject);
        Insert(pObject);
    }
}

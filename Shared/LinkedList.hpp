#ifndef LINKED_LIST_HPP
#define LINKED_LIST_HPP

template <class T>
class LinkedList
{
public:
    LinkedList();
    LinkedList(LinkedList* pPrev, T* pData);
    virtual ~LinkedList();

    void Unlink();
    LinkedList* Next() const;
    T* Data() const;
    void Insert(T* pData);

    template <class F>
    void Foreach(F Func);

private:
    LinkedList* pPrev;
    LinkedList* pNext;
    T* pData;
};

template <class T>
LinkedList<T>::LinkedList() :
LinkedList(nullptr, nullptr)
{
}

template <class T>
LinkedList<T>::LinkedList(LinkedList* pPrev, T* pData) :
pPrev(pPrev),
pNext(nullptr),
pData(pData)
{
}

template <class T>
LinkedList<T>::~LinkedList()
{
    delete pNext; // Domino effect
}

template <class T>
LinkedList<T>* LinkedList<T>::Next() const
{
    return pNext;
}

template <class T>
T* LinkedList<T>::Data() const
{
    return pData;
}

template <class T>
void LinkedList<T>::Unlink()
{
    if (pPrev) pPrev->pNext = pNext;
    if (pNext) pNext->pPrev = pPrev;
    delete this;
}

template <class T>
void LinkedList<T>::Insert(T* pData)
{
    if (!pData)
        this->pData = pData;
    else
    {
        LinkedList* pIter = this, *pNew;
        while (pIter->pNext) pIter = pIter->Next();
        pNew = new LinkedList(pIter, pData);
        pIter->pNext = pNew;
    }
}

template <class T> template <class F>
void LinkedList<T>::Foreach(F Func)
{
    for (LinkedList* pIter = this; pIter != nullptr; pIter = pIter->Next())
        if (T* pObject = pIter->Data())
            Func(pObject);
}
#endif

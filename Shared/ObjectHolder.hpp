#ifndef OBJECT_HOLDER_HPP
#define OBJECT_HOLDER_HPP

#include "Shared/BasicTypes.hpp"

#include <unordered_map>
#include <algorithm>

template <class T>
class ObjectHolder
{
public:
    static void Insert(T* pObject);
    static void Erase(T* pObject);
    static T* Find(uint64 GUID);

private:
    ObjectHolder() {}
    static std::unordered_map<uint64, T*> ObjectMap;
};

template <class T> std::unordered_map<uint64, T*> ObjectHolder<T>::ObjectMap;

template <class T> void ObjectHolder<T>::Insert(T* pObject)
{
    ObjectMap[pObject->GetGUID()] = pObject;
}

template <class T> void ObjectHolder<T>::Erase(T* pObject)
{
    ObjectMap.erase(pObject->GetGUID());
}

template <class T> T* ObjectHolder<T>::Find(uint64 GUID)
{
    typename std::unordered_map<uint64, T*>::iterator itr = ObjectMap.find(GUID);
    return (itr != ObjectMap.end()) ? itr->second : nullptr;
}

#endif

#ifndef GRID_HPP
#define GRID_HPP

#include <SFML/System/Vector2.hpp>
#include <vector>
#include <algorithm>
#include <memory>

template <class T>
using Vector2 = sf::Vector2<T>;

template <class T>
class Grid
{
public:
    Grid(uint16 x, uint16 y);
    ~Grid();

    T* At(Vector2<uint16> const& Pos);
    T* At(uint16 x, uint16 y);
    void Insert(T* What);
    uint16 GetSizeX() const;
    uint16 GetSizeY() const;

private:
    Vector2<uint16> Size;
    std::vector<T*> Array;
};

template <class T>
Grid<T>::Grid(uint16 x, uint16 y)
{
    Size.x = x;
    Size.y = y;
    Array.resize(x * y, nullptr);
    for (uint32 i = 0; i < uint32(x) * uint32(y); ++i)
        Array[i] = new T;
}

template <class T>
Grid<T>::~Grid()
{
    std::for_each(Array.begin(), Array.end(), std::default_delete<T>());
}

template <class T>
T* Grid<T>::At(Vector2<uint16> const& Pos)
{
    return At(Pos.x + Pos.y);
}

template <class T>
T* Grid<T>::At(uint16 x, uint16 y)
{
    return Array[Size.y * y + x];
}

template <class T>
uint16 Grid<T>::GetSizeX() const
{
    return Size.x;
}

template <class T>
uint16 Grid<T>::GetSizeY() const
{
    return Size.y;
}

template <class T>
void Grid<T>::Insert(T* What)
{
    Array[Size.y * What->GetPosition().y + What->GetPosition().x] = What;
}

#endif

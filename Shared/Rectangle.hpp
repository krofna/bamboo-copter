#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SFML/Graphics/Rect.hpp>

template <class T>
struct Rect : sf::Rect<T>
{
    Rect()
    {
    }

    Rect(sf::Vector2<T> NW, sf::Vector2<T> Size) : sf::Rect<T>(NW, Size)
    {
    }

    Rect(const sf::Rect<T>& Rect) : sf::Rect<T>(Rect)
    {
    }

    inline sf::Vector2<T> NW()
    {
        return sf::Vector2<T>(this->left, this->top);
    }

    inline sf::Vector2<T> Size()
    {
        return sf::Vector2<T>(this->width, this->height);
    }
};

#endif

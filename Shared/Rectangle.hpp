#ifndef RECTANGLE_HPP
#define RECTANGLE_HPP

#include <SFML/Graphics/Rect.hpp>

struct Rectangle : sf::Rect<float>
{
    Rectangle(sf::Vector2f NW, sf::Vector2f Size) : sf::Rect<float>(NW, Size)
    {
    }

    Rectangle(const sf::Rect<float>& Rect) : sf::Rect<float>(Rect)
    {
    }

    inline sf::Vector2f NW()
    {
        return sf::Vector2f(left, top);
    }

    inline sf::Vector2f Size()
    {
        return sf::Vector2f(width, height);
    }
};

#endif

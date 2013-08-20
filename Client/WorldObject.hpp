#ifndef WORLD_OBJECT_HPP
#define WORLD_OBJECT_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Graphics/Sprite.hpp>
#include "Shared/Rectangle.hpp"
#include "Shared/BasicTypes.hpp"


class CAnimationTemplate;

class WorldObject
{
public:
    WorldObject(uint32 Entry);

    Rectangle<float> GetRect() const;
    void Draw(sf::RenderWindow& Window);
    void Update();
    void SetPosition(sf::Vector2f NewPos);
    sf::Vector2f GetPosition() const;
    void SetAnimation(uint8 NewAnim);
    void SetAnimationSpeed(sf::Time Speed);
    void SetSize(sf::Vector2f Size);

private:
    // Move some to Animation?
    sf::Sprite Sprite;
    uint8 TexPosIter;
    uint8 CurrAnim;
    sf::Vector2f Size; // Sprite.getLocalBounds??
    sf::Time Speed, Elapsed;
    CAnimationTemplate* pTemplate;
};

#endif

#include "WorldObject.hpp"
#include "Shared/DataMgr.hpp"
#include "Shared/Defines.hpp"

WorldObject::WorldObject(uint32 Entry) :
CurrAnim(0)
{
    pTemplate = sDataMgr->GetAnimationTemplate(Entry);
    Sprite.setTexture(*pTemplate->pTexture);
    this->Size = sf::Vector2f(pTemplate->Size);
}

Rect<float> WorldObject::GetRect() const
{
    return Rect<float>(Sprite.getPosition(), Size);
}

void WorldObject::Draw(sf::RenderWindow& Window)
{
    Window.draw(Sprite);
}

void WorldObject::Update()
{
    Elapsed += sf::milliseconds(GAME_HEARTBEAT);
    while (Elapsed > Speed)
    {
        Elapsed -= Speed;
        if (++TexPosIter == pTemplate->FramesPerAnim[CurrAnim])
            TexPosIter = 0;
        Sprite.setTextureRect(sf::IntRect(sf::Vector2i(pTemplate->TexPos[CurrAnim][TexPosIter]), sf::Vector2i(Size)));
    }
}

void WorldObject::SetPosition(sf::Vector2f NewPos)
{
    Sprite.setPosition(NewPos);
}

sf::Vector2f WorldObject::GetPosition() const
{
    return Sprite.getPosition();
}

void WorldObject::SetAnimation(uint8 NewAnim)
{
    CurrAnim = NewAnim;
    TexPosIter = 0;
}

void WorldObject::SetAnimationSpeed(sf::Time Speed)
{
    this->Speed = Speed;
}

void WorldObject::SetSize(sf::Vector2f Size)
{
    this->Size = Size;
}

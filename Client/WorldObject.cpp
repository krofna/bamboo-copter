#include "WorldObject.hpp"
#include "Shared/DataMgr.hpp"
#include "Shared/Defines.hpp"

WorldObject::WorldObject(uint32 Entry, uint64 GUID) :
TexPosIter(0),
CurrAnim(0),
GUID(GUID)
{
    pTemplate = sDataMgr->GetAnimationTemplate(Entry);
    Sprite.setTexture(*pTemplate->pTexture);
    this->Size = sf::Vector2f(pTemplate->Size);
    Sprite.setTextureRect(sf::IntRect(sf::Vector2i(pTemplate->TexPos[0][0]), sf::Vector2i(Size)));
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
    Sprite.setTextureRect(sf::IntRect(sf::Vector2i(pTemplate->TexPos[CurrAnim][TexPosIter]), sf::Vector2i(Size)));
}

void WorldObject::SetAnimationSpeed(sf::Time Speed)
{
    this->Speed = Speed;
}

void WorldObject::SetSize(sf::Vector2f Size)
{
    this->Size = Size;
}

uint64 WorldObject::GetGUID() const
{
    return GUID;
}

void WorldObject::Move(uint16 x, uint16 y)
{
    // TODO: Flip animation from standing to moving
    // TODO: "Jump" (Lag) to previous location if not reached
    // TODO: Start sliding towards x and y
    Sprite.setPosition(x, y); // Placeholder
}

void WorldObject::MoveX(uint16 x)
{
    Sprite.setPosition(sf::Vector2<float>(x, GetPosition().y));
}

void WorldObject::MoveY(uint16 y)
{
    Sprite.setPosition(sf::Vector2<float>(GetPosition().x, y));
}

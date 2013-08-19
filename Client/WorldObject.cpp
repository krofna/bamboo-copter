#include "WorldObject.hpp"
#include "DataMgr.hpp"
#include "GameState.hpp"

WorldObject::WorldObject(uint32 Entry)
{
    pTemplate = sDataMgr->GetAnimationTemplate(Entry);
    Sprite.setTexture(*pTemplate->pTexture);
}

Rectangle WorldObject::GetRect() const
{
    return Rectangle(Sprite.getPosition(), Size);
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

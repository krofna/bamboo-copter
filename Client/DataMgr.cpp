#include "DataMgr.hpp"
#include "WorldObject.hpp"
#include <SFML/Graphics/Texture.hpp>
#include "Shared/Defines.hpp"

DataMgr* sDataMgr;

DataMgr::~DataMgr()
{
}

void DataMgr::ProcessPacket(Packet& Pckt)
{
    uint8 Type;
    uint32 Entry;
    Pckt >> Entry >> Type;

    switch (Type)
    {
        case NULL_TEMPLATE: assert(false);
        case ANIMATION_TEMPLATE: Animations[Entry] = LoadAnimationTemplate(Pckt); break;
        default: assert(false);
    }
}

CAnimationTemplate* DataMgr::GetAnimationTemplate(uint32 Entry)
{
    return &Animations[Entry];
}

CAnimationTemplate DataMgr::LoadAnimationTemplate(Packet& Pckt)
{
    CAnimationTemplate Template;
    std::string Texture;
    uint8 NumAnims;
    uint8 NumFrames;
    uint8 x, y;

    Pckt >> Texture;
    Template.pTexture = new sf::Texture;
    Template.pTexture->loadFromFile(Texture);
    Pckt >> NumAnims;
    Template.FramesPerAnim.resize(NumAnims);
    Template.TexPos.resize(NumAnims);
    for (uint8 i = 0; i < NumAnims; ++i)
    {
        Pckt >> NumFrames;
        Template.FramesPerAnim[i] = NumFrames;
        Template.TexPos[i].resize(NumFrames);
        for (int j = 0; j < NumFrames; ++j)
        {
            Pckt >> x >> y;
            Template.TexPos[i][j] = sf::Vector2<uint16>(x * TILE_SIZE, y * TILE_SIZE);
        }
    }
    return Template;
}

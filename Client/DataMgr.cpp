#include "DataMgr.hpp"
#include "WorldObject.hpp"
#include <SFML/Graphics/Texture.hpp>
#include "Shared/Defines.hpp"

DataMgr* sDataMgr;

DataMgr::DataMgr()
{

}

DataMgr::~DataMgr()
{
}

void DataMgr::ProcessPacket(Packet& Pckt)
{
    std::string Path;
    uint8 Type;

    Pckt >> Path >> Type;
    File DataFile(Path, std::ios::in);
    switch (Type)
    {
        case NULL_TEMPLATE: assert(false);
        case ANIMATION_TEMPLATE: ProcessAnimationTemplateFile(DataFile); break;
        default: assert(false);
    }
}

CAnimationTemplate* DataMgr::GetAnimationTemplate(uint32 Entry)
{
    auto i = Animations.find(Entry);
    if (i != Animations.end())
        return &i->second;
    return nullptr;
}

void DataMgr::ProcessAnimationTemplateFile(File& DataFile)
{
    CAnimationTemplate Template;
    uint32 Entry;
    std::string Texture;
    uint8 NumAnims;
    uint8 NumFrames;
    uint8 x, y;
    uint16 sx, sy;

    while (true)
    {
        DataFile >> Entry;
        if (!DataFile) break;
        DataFile >> Texture;
        Template.pTexture = new sf::Texture;
        Template.pTexture->loadFromFile(Texture);
        DataFile >> sx >> sy;
        Template.Size = sf::Vector2<uint16>(sx, sy);
        DataFile >> NumAnims;
        Template.FramesPerAnim.resize(NumAnims);
        Template.TexPos.resize(NumAnims);
        for (uint8 i = 0; i < NumAnims; ++i)
        {
            DataFile >> NumFrames;
            Template.FramesPerAnim[i] = NumFrames;
            Template.TexPos[i].resize(NumFrames);
            for (int j = 0; j < NumFrames; ++j)
            {
                DataFile >> x >> y;
                Template.TexPos[i][j] = sf::Vector2<uint16>(x * TILE_SIZE, y * TILE_SIZE);
            }
        }
        Animations[Entry] = Template;
    }
}

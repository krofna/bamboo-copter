#include "DataMgr.hpp"
#include "WorldObject.hpp"
#include "Shared/Defines.hpp"

#ifdef CLIENT
#include <SFML/Graphics/Texture.hpp>
#endif

DataMgr* sDataMgr;

DataMgr::DataMgr()
{

}

DataMgr::~DataMgr()
{
}

void DataMgr::LoadFile(std::string FileName)
{
    File DataFile(FileName, std::ios::in);
    ProcessAnimationTemplateFile(DataFile);
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
#ifdef CLIENT
        Template.pTexture = new sf::Texture;
        Template.pTexture->loadFromFile(Texture);
#endif
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

#include "DataMgr.hpp"
#include "Shared/Defines.hpp"
#include "Shared/Log.hpp"

#ifdef CLIENT
#include <SFML/Graphics/Texture.hpp>
#endif

DataMgr* sDataMgr;

DataMgr::DataMgr()
{
}

DataMgr::~DataMgr()
{
    // TODO: Deallocate textures
}

void DataMgr::LoadFile(std::string FileName)
{
    File DataFile(FileName, std::ios::in);
    uint8 Type;
    DataFile >> Type;
    switch (Type)
    {
        case ANIMATION_TEMPLATE: ProcessAnimationTemplateFile(DataFile); break;
        case CREATURE_TEMPLATE: ProcessCreatureTemplateFile(DataFile); break;
        case TERRAIN_TEMPLATE: ProcessTerrainTemplateFile(DataFile); break;
        default: sLog.Write(LOG_ERROR, "Invalid Template file"); break;
    }
}

CAnimationTemplate* DataMgr::GetAnimationTemplate(uint32 Entry)
{
    auto i = Animations.find(Entry);
    if (i != Animations.end())
        return &i->second;
    return nullptr;
}

CreatureTemplate* DataMgr::GetCreatureTemplate(uint32 Entry)
{
    auto i = CreatureTemplates.find(Entry);
    if (i != CreatureTemplates.end())
        return &i->second;
    return nullptr;
}

TerrainTemplate* DataMgr::GetTerrainTemplate(uint32 Entry)
{
    auto i = TerrainTemplates.find(Entry);
    if (i != TerrainTemplates.end())
        return &i->second;
    return nullptr;
}

HeroTemplate* DataMgr::GetHeroTemplate(uint32 Entry)
{
    // placeholder
    static HeroTemplate t;
    t.Entry = Entry;
    return &t;
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

    while (DataFile >> Entry)
    {
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

void DataMgr::ProcessCreatureTemplateFile(File& DataFile)
{
    CreatureTemplate Template;

    while (DataFile >> Template.Entry)
    {
        DataFile >> Template.ScriptName;
        CreatureTemplates[Template.Entry] = Template;
    }
}

void DataMgr::ProcessTerrainTemplateFile(File& DataFile)
{
    TerrainTemplate Template;
    std::string Texture;

    while (DataFile >> Template.Entry)
    {
        DataFile >> Texture;
#ifdef CLIENT
        Template.pTexture = new sf::Texture;
        Template.pTexture->loadFromFile(Texture);
#endif
        DataFile >> Template.TexPos.x >> Template.TexPos.y >> Template.Size.x >> Template.Size.y;
        TerrainTemplates[Template.Entry] = Template;
    }
}

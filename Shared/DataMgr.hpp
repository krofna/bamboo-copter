#ifndef DATA_MGR_HPP
#define DATA_MGR_HPP

#include <map>
#include "Shared/Packet.hpp"
#include "Shared/Templates.hpp"
#include "Shared/File.hpp"

class DataMgr
{
public:
	DataMgr();
    ~DataMgr();

    void LoadFile(std::string FileName);

    CAnimationTemplate* GetAnimationTemplate(uint32 Entry);
    CreatureTemplate* GetCreatureTemplate(uint32 Entry);
    HeroTemplate* GetHeroTemplate(uint32 Entry);
    TerrainTemplate* GetTerrainTemplate(uint32 Entry);

private:
    void ProcessTerrainTemplateFile(File& DataFile);
    void ProcessCreatureTemplateFile(File& DataFile);
    void ProcessAnimationTemplateFile(File& DataFile);
    std::map<uint32, CAnimationTemplate> Animations;
    std::map<uint32, CreatureTemplate> CreatureTemplates;
    std::map<uint32, HeroTemplate> HeroTemplates;
    std::map<uint32, TerrainTemplate> TerrainTemplates;
};

extern DataMgr* sDataMgr;

#endif

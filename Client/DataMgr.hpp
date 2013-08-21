#ifndef DATA_MGR_HPP
#define DATA_MGR_HPP

#include <map>
#include "Shared/Packet.hpp"
#include "Shared/Templates.hpp"
#include "Shared/File.hpp"

class WorldObject;

class DataMgr
{
public:
	DataMgr();
    ~DataMgr();

    void ProcessPacket(Packet& Pckt);
    CAnimationTemplate* GetAnimationTemplate(uint32 Entry);

private:
    void ProcessAnimationTemplateFile(File& DataFile);
    std::map<uint32, CAnimationTemplate> Animations;
};

extern DataMgr* sDataMgr;

#endif

#ifndef DATA_MGR_HPP
#define DATA_MGR_HPP

#include <map>
#include "Shared/Packet.hpp"
#include "Shared/Templates.hpp"

class WorldObject;

class DataMgr
{
public:
    ~DataMgr();

    void ProcessPacket(Packet& Pckt);

    CAnimationTemplate* GetAnimationTemplate(uint32 Entry);

private:
    CAnimationTemplate LoadAnimationTemplate(Packet& Pckt);

    std::map<uint32, CAnimationTemplate> Animations;
};

extern DataMgr* sDataMgr;

#endif

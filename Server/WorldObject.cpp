#include "WorldObject.hpp"
#include "Player.hpp"
#include "Shared/Opcodes.hpp"
#include "Shared/DataMgr.hpp"

WorldObject::WorldObject(uint64 GUID, uint32 Entry) :
GUID(GUID),
Entry(Entry)
{
    CAnimationTemplate* pTemplate = sDataMgr->GetAnimationTemplate(Entry);
    Rectg.width = pTemplate->Size.x;
    Rectg.height = pTemplate->Size.y;
}

Rect<uint32> WorldObject::GetRect() const
{
    return Rectg;
}

uint64 WorldObject::GetGUID() const
{
    return GUID;
}

Map* WorldObject::GetMap() const
{
    return pMap;
}

void WorldObject::Update()
{
}

void WorldObject::CreateForPlayer(Player* pPlayer)
{
    Packet Pckt(SMSG_OBJECT_CREATE);
    Pckt << GUID << Entry << Rectg.left << Rectg.top;
    pPlayer->SendPacket(Pckt);
}


void WorldObject::Relocate(Map* pMap, uint32 x, uint32 y)
{
    this->pMap = pMap;
    Relocate(x, y);
}

void WorldObject::Relocate(uint32 x, uint32 y)
{
    Rectg.left = x;
    Rectg.top = y;
}

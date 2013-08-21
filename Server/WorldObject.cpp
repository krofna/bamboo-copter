#include "WorldObject.hpp"
#include "Player.hpp"
#include "Shared/Opcodes.hpp"

WorldObject::WorldObject(uint64 GUID, uint32 Entry) :
GUID(GUID),
Entry(Entry)
{
}

Rectangle<uint32> WorldObject::GetRect() const
{
    return Rect;
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
    Pckt << GUID << Entry << Rect.left << Rect.top << Rect.width << Rect.height;
    pPlayer->SendPacket(Pckt);
}


void WorldObject::Relocate(Map* pMap, uint32 x, uint32 y)
{
    this->pMap = pMap;
    Relocate(x, y);
}

void WorldObject::Relocate(uint32 x, uint32 y)
{
    Rect.left = x;
    Rect.top = y;
}

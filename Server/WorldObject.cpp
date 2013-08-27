#include "WorldObject.hpp"
#include "Player.hpp"
#include "Shared/Opcodes.hpp"
#include "Shared/DataMgr.hpp"
#include "Shared/Defines.hpp"
#include "Map.hpp"
#include "Creature.hpp"
#include "Shared/ObjectHolder.hpp"

uint64 WorldObject::NextGUID;

WorldObject::WorldObject(uint64 GUID, uint32 Entry) :
GUID(GUID),
ObjectUpdate(SMSG_OBJECT_UPDATE)
{
    CAnimationTemplate* pTemplate = sDataMgr->GetAnimationTemplate(Entry);
    Rectg.width = pTemplate->Size.x;
    Rectg.height = pTemplate->Size.y;
    ObjectUpdate << GUID;
}

Rect<uint16> Object::GetRect() const
{
    return Rectg;
}

void WorldObject::SetX(uint16 x)
{
    Rectg.left = x;
    ObjectUpdate << (uint8)UPDATE_FIELD_X << x;
}

void WorldObject::SetY(uint16 y)
{
    Rectg.top = y;
    ObjectUpdate << (uint8)UPDATE_FIELD_Y << y;
}

uint16 WorldObject::GetX() const
{
    return Rectg.left;
}

uint16 WorldObject::GetY() const
{
    return Rectg.top;
}

uint64 WorldObject::GetGUID() const
{
    return GUID;
}

Map* WorldObject::GetMap() const
{
    return pMap;
}

void WorldObject::SendUpdate()
{
    // Nothing to send
    if (ObjectUpdate.GetSizeWithoutHeader() == sizeof(uint64))
        return;

    pMap->SendToPlayers(ObjectUpdate);
    ObjectUpdate = Packet(SMSG_OBJECT_UPDATE);
    ObjectUpdate << GUID;
}

void WorldObject::Update()
{
}

void WorldObject::CreateForPlayer(Player* pPlayer)
{
    Packet Pckt(SMSG_OBJECT_CREATE);
    Pckt << GUID << pTemplate->Entry << Rectg.left << Rectg.top;
    pPlayer->SendPacket(Pckt);
}

void WorldObject::Relocate(Map* pMap, uint16 x, uint16 y)
{
    this->pMap = pMap;
    SetX(x);
    SetY(y);
}

Creature* WorldObject::SummonCreature(uint32 Entry, uint16 x, uint16 y)
{
    Creature* pCreature = new Creature(WorldObject::GetNextGUID(), Entry);
    ObjectHolder<Creature>::Insert(pCreature);
    GetMap()->Insert(pCreature);
    pCreature->Relocate(GetMap(), x, y);
    return pCreature;
}

uint32 WorldObject::GetEntry() const
{
    return pTemplate->Entry;
}

WorldObjectTemplate* WorldObject::GetTemplate()
{
    return pTemplate;
}

uint64 WorldObject::GetNextGUID()
{
    return NextGUID++;
}

void Terrain::ResetPathfinderNode()
{
    Node::Reset();
}

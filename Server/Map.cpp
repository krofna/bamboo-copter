#include "Map.hpp"
#include "Shared/Database.hpp"
#include "PlayerHolder.hpp"

Map::Map(std::string Name, uint64 GUID) :
Name(Name),
MapGUID(GUID)
{
}

void Map::Update()
{
    QuadTree::Traverse(std::bind(&WorldObject::Update, std::placeholders::_1));
}

void Map::LoadObjects()
{
    QueryResult Result;
    WorldObject* pObject;
    uint32 Entry, x, y;
    uint64 GUID;
    std::string Name;

    Result = sDatabase.PQuery("SELECT `guid`, `entry`, `x`, `y`, `username` FROM `players` WHERE map='%llu'", MapGUID);
    while (Result->next())
    {
        GUID  = Result->getUInt64(1);
        Entry = Result->getUInt  (2);
        x     = Result->getUInt  (3);
        y     = Result->getUInt  (4);
        Name  = Result->getString(5);
        pObject = new Player(GUID, Entry, Name);
        pObject->Relocate(this, x, y);
        QuadTree::Insert(pObject);
        ObjectHolder<Player>::Insert((Player*)pObject);
    }
}

void Map::AddPlayer(Player* pPlayer)
{
    // Send current state
    QuadTree::Traverse(std::bind(&WorldObject::CreateForPlayer, std::placeholders::_1, pPlayer));

    // Make sure player receives new updates
    OnlinePlayers.Insert(pPlayer);
}

void Map::SendToPlayers(Packet& Pckt)
{
    OnlinePlayers.Foreach(std::bind(&Player::SendPacket, std::placeholders::_1, std::ref(Pckt)));
}

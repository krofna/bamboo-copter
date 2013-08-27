#include "Map.hpp"
#include "Shared/Database.hpp"
#include "PlayerHolder.hpp"
#include "Creature.hpp"

Map::Map(std::string Name, uint64 GUID, uint16 Width, uint16 Height) :
QuadTree(sf::Rect<uint16>(0, 0, Width, Height), nullptr),
Objects(sf::Rect<uint16>(0, 0, Width, Height), nullptr),
Name(Name),
MapGUID(GUID)
{
}

void Map::Update()
{
    Objects.Traverse(std::bind(&WorldObject::Update, std::placeholders::_1));
    Objects.Traverse(std::bind(&WorldObject::SendUpdate, std::placeholders::_1));
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
        Objects.Insert(pObject);
        ObjectHolder<Player>::Insert((Player*)pObject);
    }

    Result = sDatabase.PQuery("SELECT `guid`, `entry`, `x`, `y`, `scriptname` FROM `creature` WHERE map='%llu'", MapGUID);
    while (Result->next())
    {
        GUID  = Result->getUInt64(1);
        Entry = Result->getUInt  (2);
        x     = Result->getUInt  (3);
        y     = Result->getUInt  (4);
        Name  = Result->getString(5); // Scriptname
        pObject = new Creature(GUID, Entry, Name);
        pObject->Relocate(this, x, y);
        Objects.Insert(pObject);
        ObjectHolder<Creature>::Insert((Creature*)pObject);
    }
}

void Map::AddPlayer(Player* pPlayer)
{
    // Send current state
    Objects.Traverse(std::bind(&WorldObject::CreateForPlayer, std::placeholders::_1, pPlayer));

    // Make sure player receives new updates
    OnlinePlayers.Insert(pPlayer);
}

void Map::SendToPlayers(Packet& Pckt)
{
    OnlinePlayers.Foreach(std::bind(&Player::SendPacket, std::placeholders::_1, std::ref(Pckt)));
}

LinkedList<WorldObject>* Map::At(Rect<uint16> Where)
{
    ::LinkedList<WorldObject>* ObjectList = new LinkedList<WorldObject>;
    Objects.TraverseArea(Where, std::bind(&::LinkedList<WorldObject>::Insert, ObjectList, std::placeholders::_1));
    return ObjectList;
}

WorldObject* Map::At(uint16 X, uint16 Y, uint16 Size)
{
    return At(sf::Rect<uint16>(X, Y, Size, Size))->Data();
}

LinkedList<Terrain>* Map::TerrainAt(Rect<uint16> Where)
{
    ::LinkedList<Terrain>* ObjectList = new LinkedList<Terrain>;
    QuadTree::TraverseArea(Where, std::bind(&::LinkedList<Terrain>::Insert, ObjectList, std::placeholders::_1));
    return ObjectList;
}

Terrain* Map::TerrainAt(uint16 X, uint16 Y, uint16 Size)
{
    /* TODO: Depend on terrain level*/
    return TerrainAt(sf::Rect<uint16>(X, Y, Size, Size))->Data();
}

void Map::ResetPathfinderNodes()
{
    QuadTree::Traverse(std::bind(&Terrain::ResetPathfinderNode, std::placeholders::_1));
}

uint64 Map::GetGUID()
{
    return MapGUID;
}

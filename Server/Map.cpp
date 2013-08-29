#include "Map.hpp"
#include "Shared/Database.hpp"
#include "PlayerHolder.hpp"
#include "Creature.hpp"

Map::Map(std::string Name, uint64 GUID, uint16 Width, uint16 Height) :
QuadTree(sf::Rect<uint16>(0, 0, Width, Height), nullptr),
Name(Name),
MapGUID(GUID)
{
    Entry = 0; // PLACEHOLDER
}

void Map::Update()
{
    QuadTree::Traverse(std::bind(&WorldObject::Update, std::placeholders::_1));
    QuadTree::Traverse(std::bind(&WorldObject::SendUpdate, std::placeholders::_1));
}

void SetNextGUID(uint64 GUID)
{
    WorldObject::NextGUID = GUID;
}

void Map::LoadObjects()
{
    QueryResult Result;
    WorldObject* pObject;
    uint32 Entry, x, y;
    uint64 GUID, MaxGUID = 0;
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
        Insert(pObject);
        ObjectHolder<Player>::Insert((Player*)pObject);

        if (GUID > MaxGUID)
            MaxGUID = GUID;
    }

    Result = sDatabase.PQuery("SELECT `guid`, `entry`, `x`, `y` FROM `creature` WHERE map='%llu'", MapGUID);
    while (Result->next())
    {
        GUID  = Result->getUInt64(1);
        Entry = Result->getUInt  (2);
        x     = Result->getUInt  (3);
        y     = Result->getUInt  (4);
        pObject = new Creature(GUID, Entry);
        pObject->Relocate(this, x, y);
        Insert(pObject);
        ObjectHolder<Creature>::Insert((Creature*)pObject);

        if (GUID > MaxGUID)
            MaxGUID = GUID;
    }

    SetNextGUID(MaxGUID + 1);
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

LinkedList<WorldObject>* Map::At(Rect<uint16> Where)
{
    ::LinkedList<WorldObject>* ObjectList = new LinkedList<WorldObject>;
    QuadTree::TraverseArea(Where, std::bind(&::LinkedList<WorldObject>::Insert, ObjectList, std::placeholders::_1));
    return ObjectList;
}

WorldObject* Map::At(uint16 X, uint16 Y, uint16 Size)
{
    return At(sf::Rect<uint16>(X, Y, Size, Size))->Data();
}

void Map::ResetPathfinderNodes()
{
    //QuadTree::Traverse(std::bind(&::Node::Reset, std::placeholders::_1));
}

Node* Map::TerrainAt(uint16 X, uint16 Y, uint16 Size)
{
    return QuadTree::At(sf::Rect<uint16>(X, Y, Size, Size));
}

uint64 Map::GetGUID() const
{
    return MapGUID;
}

uint32 Map::GetEntry() const
{
    return Entry;
}

void Map::Insert(WorldObject* pObject)
{
    QuadTree::Insert(pObject);
}

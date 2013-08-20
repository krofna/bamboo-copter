#include "Map.hpp"
#include "Shared/Database.hpp"
#include "Player.hpp"

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

    Result = sDatabase.PQuery("SELECT `guid`, `entry`, `x`, `y` FROM `players` WHERE map='%llu'", MapGUID);
    while (Result->next())
    {
        GUID  = Result->getUInt64(1);
        Entry = Result->getUInt  (2);
        x     = Result->getUInt  (3);
        y     = Result->getUInt  (4);
        pObject = new Player(GUID, Entry, x, y);
        QuadTree::Insert(pObject);
    }
}

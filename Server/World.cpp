#include "World.hpp"
#include "Shared/Database.hpp"
#include "Shared/DataMgr.hpp"
#include "Pathfinder.hpp"

#define HEARTBEAT 50

World* sWorld;

World::World(boost::asio::io_service& io) :
UpdateTimer(io),
io(io)
{
    sDataMgr = new DataMgr;
    sPathfinder = new Pathfinder;
}

World::~World()
{
    delete sDataMgr;
    delete sPathfinder;
}

void World::Load()
{
    sDataMgr->LoadFile("../Shared/test.tem");

    sDatabase.Connect();
    QueryResult Result(sDatabase.PQuery("SELECT `name`, `guid`, `width`, `height` FROM `maps`"));
    std::string MapName;
    uint64 MapGUID;
    uint16 Width, Height;

    while (Result->next())
    {
        MapName = Result->getString(1);
        MapGUID = Result->getUInt64(2);
        Width = Result->getUInt(3);
        Height = Result->getUInt(4);
        Map* pMap = new Map(MapName, MapGUID, Width, Height);
        pMap->LoadObjects();
        LinkedList::Insert(pMap);
    }

    UpdateTimer.expires_from_now(boost::posix_time::milliseconds(HEARTBEAT));
    UpdateTimer.async_wait(std::bind(&World::Run, this));
}

void World::Run()
{
    Update();
    UpdateTimer.expires_at(UpdateTimer.expires_at() + boost::posix_time::milliseconds(HEARTBEAT));
    UpdateTimer.async_wait(std::bind(&World::Run, this));
}

void World::Update()
{
    Foreach(std::bind(&Map::Update, std::placeholders::_1));
}

void World::ResetPathfinderNodes()
{
    Foreach(std::bind(&Map::ResetPathfinderNodes, std::placeholders::_1));
}

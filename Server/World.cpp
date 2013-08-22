#include "World.hpp"
#include "Shared/Database.hpp"
#include "Shared/DataMgr.hpp"
#include "Map.hpp"

#define HEARTBEAT 50

World::World(boost::asio::io_service& io) :
UpdateTimer(io),
io(io)
{
}

World::~World()
{
    delete sDataMgr;
}

void World::Load()
{
    sDataMgr = new DataMgr;
    sDataMgr->LoadFile("../Shared/test.tem");

    sDatabase.Connect();
    QueryResult Result(sDatabase.PQuery("SELECT `name`, `guid` FROM `maps`"));
    std::string MapName;
    uint64 MapGUID;

    while (Result->next())
    {
        MapName = Result->getString(1);
        MapGUID = Result->getUInt64(2);
        Map* pMap = new Map(MapName, MapGUID);
        pMap->LoadObjects();
    }

    io.post(std::bind(&World::Run, this));
}

void World::Run()
{
    Update();
    UpdateTimer.expires_at(UpdateTimer.expires_at() + boost::posix_time::milliseconds(HEARTBEAT));
    UpdateTimer.async_wait(std::bind(&World::Run, this));
}

void World::Update()
{
}

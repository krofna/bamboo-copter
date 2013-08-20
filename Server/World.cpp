#include "World.hpp"
#include "Shared/Database.hpp"
#include "Map.hpp"
#include <thread>
#include <chrono>

#define HEARTBEAT 50

World::World(boost::asio::io_service& io) :
io(io)
{
}

void World::Load()
{
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
}

void World::Run()
{
    std::chrono::steady_clock::time_point OldTime, Elapsed;
    OldTime = std::chrono::steady_clock::now();
    while (true)
    {
        Elapsed += std::chrono::steady_clock::now() - OldTime;
        while (Elapsed.time_since_epoch() > std::chrono::milliseconds(HEARTBEAT))
        {
            Elapsed -= std::chrono::milliseconds(HEARTBEAT);
            Update();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(HEARTBEAT) - std::chrono::duration_cast<std::chrono::milliseconds>(Elapsed.time_since_epoch()));
    }
}

void World::Update()
{
}

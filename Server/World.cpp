#include "World.hpp"
#include "Shared/Database.hpp"
#include "Shared/DataMgr.hpp"
#include "Pathfinder.hpp"
#include "Shared/Defines.hpp"
#include <boost/thread/thread.hpp>
#include <boost/bind/bind.hpp>

World* sWorld;

extern void LoadScripts();

World::World(boost::asio::io_service& io) :
IsRunning(true),
UpdateTimer(io),
io(io)
{
    sDataMgr = new DataMgr;
    sPathfinder = new Pathfinder(io);
}

World::~World()
{
    delete sDataMgr;
    delete sPathfinder;
}

void World::Load()
{
    LoadScripts();
    sDataMgr->LoadFile("../Shared/test.tem");
    sDataMgr->LoadFile("../Shared/CreatureTemplate.tem");
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
    }}

void World::Run()
{
    UpdateTimer.expires_from_now(boost::posix_time::milliseconds(HEARTBEAT));
    UpdateTimer.async_wait(std::bind(&World::Update, this));

    std::vector<boost::shared_ptr<boost::thread> > threads;
    for (size_t i = 0; i < 2; ++i)
    {
        boost::shared_ptr<boost::thread> thread(new boost::thread(boost::bind(&boost::asio::io_service::run, &io)));
        threads.push_back(thread);
    }

    for (size_t i = 0; i < threads.size(); ++i)
        threads[i]->join();
}

void World::Update()
{
    Foreach(std::bind(&Map::Update, std::placeholders::_1));
    UpdateTimer.expires_at(UpdateTimer.expires_at() + boost::posix_time::milliseconds(HEARTBEAT));
    UpdateTimer.async_wait(std::bind(&World::Update, this));
}

void World::ResetPathfinderNodes()
{
    Foreach(std::bind(&Map::ResetPathfinderNodes, std::placeholders::_1));
}

Map* World::GetMap(uint64 GUID)
{
    for (LinkedList* i = this; i != nullptr; i = i->Next())
        if (i->Data()->GetGUID() == GUID)
            return i->Data();
    return nullptr;
}

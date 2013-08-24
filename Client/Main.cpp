#include "Shared/Game.hpp"
#include "Shared/DataMgr.hpp"
#include "CWorld.hpp"
#include "WorldSession.hpp"
#include "Shared/Log.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>

void GenDummyTemplateFile()
{
    File f("test.tem", std::ios::out);
    f << uint32(0) << std::string("test.png") << uint16(TILE_SIZE) << uint16(TILE_SIZE) << uint8(1) << uint8(2) << uint8(0) << uint8(0) << uint8(1) << uint8(0);
    f.Close();
}

WorldSessionPtr StartNetworking(boost::asio::io_service& io)
{
    WorldSessionPtr pSession = boost::make_shared<WorldSession>(io);
    pSession->Connect("127.0.0.1", "48879");
    boost::thread NetworkingThread(boost::bind(&boost::asio::io_service::run, &io));
    NetworkingThread.detach();
    return pSession;
}

int main(int argc, char** argv)
{
    boost::asio::io_service io;
    sLog.SetPriority(LOG_INFO);

    sDataMgr = new DataMgr;
    sDataMgr->LoadFile("../Shared/test.tem");
    Game* pGame = new Game("bamboo-copter");
    World* pWorld = new CWorld(pGame->GetWindow(), StartNetworking(io));

    pGame->PushState(pWorld);
    pGame->Run();

    io.stop();
    delete pWorld;
    delete pGame;
    delete sDataMgr;
    return 0;
}

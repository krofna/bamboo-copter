#include "Shared/Game.hpp"
#include "DataMgr.hpp"
#include "Shared/World.hpp"
#include "WorldSession.hpp"
#include "Shared/Opcodes.hpp"

#include <boost/asio/io_service.hpp>
#include <boost/make_shared.hpp>
#include <boost/thread.hpp>

void GenDummyTemplateFile()
{
    File f("test.tem", std::ios::out);
    f << uint32(1) << std::string("test.png") << uint16(TILE_SIZE) << uint16(TILE_SIZE) << uint8(1) << uint8(2) << uint8(0) << uint8(0) << uint8(1) << uint8(0);
    f.Close();
}

void StartNetworking(boost::asio::io_service& io, World* pWorld)
{
    WorldSessionPtr pSession = boost::make_shared<WorldSession>(io, pWorld);
    pSession->Connect("127.0.0.1", "48879");
    boost::thread NetworkingThread(boost::bind(&boost::asio::io_service::run, &io));
    NetworkingThread.detach();
}

int main(int argc, char** argv)
{
    boost::asio::io_service io;
    Packet Pckt(SMSG_TEMPLATE);
    Pckt << "test.tem" << uint8(ANIMATION_TEMPLATE);
    sDataMgr = new DataMgr;
    sDataMgr->ProcessPacket(Pckt);
    Game* pGame = new Game("beech-copter");
    World* pWorld = new World(pGame->GetWindow());

    StartNetworking(io, pWorld);

    for (int i = 0; i < 32; ++i)
    {
        for (int j = 0; j < 32; ++j)
        {
            WorldObject* pObject = new WorldObject(1);
            pObject->SetPosition(sf::Vector2f(TILE_SIZE * float(i), TILE_SIZE * float(j)));
            pObject->SetAnimation(0);
            pObject->SetAnimationSpeed(sf::milliseconds(300));
            pWorld->Insert(pObject);
        }
    }

    pGame->PushState(pWorld);
    pGame->Run();

    io.stop();
    delete pWorld;
    delete pGame;
    delete sDataMgr;
    return 0;
}

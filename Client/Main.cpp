#include "Game.hpp"
#include "DataMgr.hpp"
#include "Shared/World.hpp"
#include "Shared/Opcodes.hpp"

int main(int argc, char** argv)
{
    Packet Pckt(SMSG_TEMPLATE);
    Pckt << uint32(1) << uint8(ANIMATION_TEMPLATE) << "test.png" << uint8(1) << uint8(2) << uint8(0) << uint8(0) << uint8(1) << uint8(0);
    sDataMgr = new DataMgr;
    sDataMgr->ProcessPacket(Pckt);
    Game* pGame = new Game;
    World* pWorld = new World(pGame->GetWindow());
    for (int i = 0; i < 32; ++i)
    {
        for (int j = 0; j < 32; ++j)
        {
            WorldObject* pObject = new WorldObject(1);
            pObject->SetPosition(sf::Vector2f(TILE_SIZE * float(i), TILE_SIZE * float(j)));
            pObject->SetAnimation(0);
            pObject->SetAnimationSpeed(sf::seconds(1));
            pObject->SetSize(sf::Vector2f(TILE_SIZE, TILE_SIZE));
            pWorld->Insert(pObject);
        }
    }
    pGame->PushState(pWorld);
    pGame->Run();
    delete pWorld;
    delete pGame;
    delete sDataMgr;
    return 0;
}

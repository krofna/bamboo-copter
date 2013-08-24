#include "CWorld.hpp"

CWorld::CWorld(sf::RenderWindow& Window, WorldSessionPtr pSession) :
World(Window),
pSession(pSession)
{
    pSession->SetWorld(this);
}

void CWorld::Draw()
{
    ObjectMutex.lock();
    World::Draw();
    ObjectMutex.unlock();
}

void CWorld::Update()
{
    ObjectMutex.lock();
    World::Update();
    ObjectMutex.unlock();
}

void CWorld::HandleEvent(sf::Event Event)
{
    World::HandleEvent(Event);

    switch (Event.type)
    {
    case sf::Event::KeyPressed:
        switch (Event.key.code)
        {
            case sf::Keyboard::W:
                pSession->SendMoveHeroPacket(MOVE_UP);
                break;
            case sf::Keyboard::A:
                pSession->SendMoveHeroPacket(MOVE_LEFT);
                break;
            case sf::Keyboard::S:
                pSession->SendMoveHeroPacket(MOVE_DOWN);
                break;
            case sf::Keyboard::D:
                pSession->SendMoveHeroPacket(MOVE_RIGHT);
            default:
                break;
        }
        break;
    default:
        break;
    }
}

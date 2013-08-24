#ifndef CWORLD_HPP
#define CWORLD_HPP

#include "Shared/World.hpp"
#include <mutex>
#include "WorldSession.hpp"

class CWorld : public World
{
public:
    CWorld(sf::RenderWindow& Window, WorldSessionPtr pSession);

    virtual void Draw();
    virtual void Update();
    virtual void HandleEvent(sf::Event Event);

private:
    std::mutex ObjectMutex;
    WorldSessionPtr pSession;
};

#endif

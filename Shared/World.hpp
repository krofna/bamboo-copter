#ifndef WORLD_HPP
#define WORLD_HPP

#include "Shared/QuadTree.hpp"
#include "Shared/GameState.hpp"
#include <mutex>

class World : private QuadTree<float>, public GameState
{
public:
    World(sf::RenderWindow& Window);
    virtual ~World();

    virtual void Draw();
    virtual void Update();
    virtual void HandleEvent(sf::Event Event);

    void Insert(WorldObject* pObject);
private:
    sf::View View;
    sf::RenderWindow& Window;
    std::mutex ObjectMutex;
};

#endif

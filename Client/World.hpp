#ifndef WORLD_HPP
#define WORLD_HPP

#include "Shared/QuadTree.hpp"
#include "GameState.hpp"

class World : public QuadTree, public GameState
{
public:
    World(sf::RenderWindow& Window);
    virtual ~World();

    virtual void Draw();
    virtual void Update();
    virtual void HandleEvent(sf::Event Event);

private:
    sf::View View;
    sf::RenderWindow& Window;
};

#endif

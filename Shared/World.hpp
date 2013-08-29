#ifndef WORLD_HPP
#define WORLD_HPP

#include "Shared/QuadTree.hpp"
#include "Shared/GameState.hpp"
#include <SFML/Graphics/VertexArray.hpp>

class WorldObject;

class World : private QuadTree<WorldObject, float, LinkedList<WorldObject> >, public GameState
{
public:
    World(sf::RenderWindow& Window);
    virtual ~World();

    virtual void Draw();
    virtual void Update();
    virtual void HandleEvent(sf::Event Event);

    void Insert(WorldObject* pObject);
    void LoadMap(uint32 Entry);
private:
    sf::VertexArray VertexArray;
    sf::View View;
    sf::RenderWindow& Window;
};

#endif

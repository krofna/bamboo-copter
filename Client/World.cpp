#include "World.hpp"
#include <limits>

#define TILE_SIZE 64

World::World(sf::RenderWindow& Window) :
QuadTree(Rectangle(sf::Vector2f(0, 0), sf::Vector2f(std::numeric_limits<uint32>::max(), std::numeric_limits<uint32>::max())), nullptr),
View(sf::FloatRect(0, 0, Window.getSize().x, Window.getSize().y)),
Window(Window)
{
}

World::~World()
{
}

void World::Draw()
{
    QuadTree::TraverseArea(View.getViewport(), std::bind(&WorldObject::Draw, std::placeholders::_1, std::ref(Window)));
}

void World::Update()
{
    QuadTree::TraverseArea(View.getViewport(), std::bind(&WorldObject::Update, std::placeholders::_1));
}

void World::HandleEvent(sf::Event Event)
{
    switch (Event.type)
    {
    case sf::Event::MouseMoved:
        if((unsigned)sf::Mouse::getPosition(Window).x >= Window.getSize().x - (TILE_SIZE / 2))
            View.move(TILE_SIZE, 0);
        else if(sf::Mouse::getPosition(Window).x < TILE_SIZE / 2)
            View.move(-TILE_SIZE, 0);
        if((unsigned)sf::Mouse::getPosition(Window).y > Window.getSize().y - (TILE_SIZE / 2))
            View.move(0, TILE_SIZE);
        else if(sf::Mouse::getPosition(Window).y < TILE_SIZE / 2)
            View.move(0, -TILE_SIZE);
        Window.setView(View);
    default:
        break;
    }
}

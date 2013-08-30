#include "World.hpp"
#include "WorldObject.hpp"
#include "Shared/File.hpp"
#include "Shared/DataMgr.hpp"
#include <SFML/Graphics/Texture.hpp>

World::World(sf::RenderWindow& Window) :
VertexArray(sf::Quads),
View(sf::FloatRect(0, 0, Window.getSize().x, Window.getSize().y)),
Window(Window)
{
}

World::~World()
{
}

void World::LoadMap(uint32 Entry)
{
    File MapFile("../Shared/TestMap.map", std::ios::in); // PLACEHOLDER
    uint32 TEntry;
    TerrainTemplate* pTemplate;
    uint32 i = 0;
    uint16 x, y, w, h;

    VertexArray.resize(4); // TODO: Map template
    while (MapFile >> TEntry)
    {
        pTemplate = sDataMgr->GetTerrainTemplate(TEntry);
        MapFile >> x >> y >> w >> h;
        VertexArray[i++] = sf::Vertex(sf::Vector2f(x, y), (sf::Vector2f(x, y)));
        VertexArray[i++] = sf::Vertex(sf::Vector2f(x + w, y), sf::Vector2f(x + w, y));
        VertexArray[i++] = sf::Vertex(sf::Vector2f(w, h), sf::Vector2f(w, h));
        VertexArray[i++] = sf::Vertex(sf::Vector2f(x, y + h), sf::Vector2f(x, y + h));
    }

    pTerrainTileset = pTemplate->pTexture;
}

void World::Draw()
{
    pTerrainTileset->setRepeated(true);
    Window.draw(VertexArray, pTerrainTileset);
    QuadTree::TraverseArea(View.getViewport(), std::bind(&WorldObject::Draw, std::placeholders::_1, std::ref(Window)));
}

void World::Update()
{
    QuadTree::TraverseArea(View.getViewport(), std::bind(&WorldObject::Update, std::placeholders::_1));
}

void World::Insert(WorldObject* pObject)
{
    QuadTree::Insert(pObject);
}

void World::HandleEvent(sf::Event Event)
{
    switch (Event.type)
    {
    case sf::Event::MouseMoved:
        if ((unsigned)sf::Mouse::getPosition(Window).x >= Window.getSize().x - (TILE_SIZE / 2))
            View.move(TILE_SIZE, 0);
        else if (sf::Mouse::getPosition(Window).x < TILE_SIZE / 2)
            View.move(-TILE_SIZE, 0);
        if ((unsigned)sf::Mouse::getPosition(Window).y > Window.getSize().y - (TILE_SIZE / 2))
            View.move(0, TILE_SIZE);
        else if (sf::Mouse::getPosition(Window).y < TILE_SIZE / 2)
            View.move(0, -TILE_SIZE);
        Window.setView(View);
        break;
    case sf::Event::KeyPressed:
        switch (Event.key.code)
        {
            case sf::Keyboard::Escape:
                Window.close();
            default:
                break;
        }
        break;
    case sf::Event::Closed:
        Window.close();
    default:
        break;
    }
}

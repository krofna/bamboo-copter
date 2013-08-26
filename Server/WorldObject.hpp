#ifndef WORLD_OBJECT_HPP
#define WORLD_OBJECT_HPP

#include "Shared/Rectangle.hpp"
#include "Shared/BasicTypes.hpp"
#include "Node.hpp"
#include "Shared/Packet.hpp"

class Map;
class Player;

class Object
{
public:
    Rect<uint16> GetRect() const;

protected:
    Rect<uint16> Rectg;
};

class WorldObject : public Object
{
public:
    WorldObject(uint64 GUID, uint32 Entry);

    uint64 GetGUID() const;
    virtual void Update();
    void CreateForPlayer(Player* pPlayer);

    Map* GetMap() const;
    void Relocate(Map* pMap, uint16 x, uint16 y);
    void SetX(uint16 x);
    void SetY(uint16 y);
    uint16 GetX() const;
    uint16 GetY() const;

    void SendUpdate();

private:
    uint64 GUID;
    uint32 Entry;
    Map* pMap;
    Packet ObjectUpdate;
};

class Terrain : public Object, public Node
{
public:
    void ResetPathfinderNode();
};

#endif

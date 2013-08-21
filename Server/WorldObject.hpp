#ifndef WORLD_OBJECT_HPP
#define WORLD_OBJECT_HPP

#include "Shared/Rectangle.hpp"
#include "Shared/BasicTypes.hpp"

class Map;
class Player;

class WorldObject
{
public:
    WorldObject(uint64 GUID, uint32 Entry);

    uint64 GetGUID() const;
    Rect<uint32> GetRect() const;
    virtual void Update();
    void CreateForPlayer(Player* pPlayer);
    Map* GetMap() const;
    void Relocate(Map* pMap, uint32 x, uint32 y);
    void Relocate(uint32 x, uint32 y);

private:
    uint64 GUID;
    uint32 Entry;
    Map* pMap;
    Rect<uint32> Rectg;
};

#endif

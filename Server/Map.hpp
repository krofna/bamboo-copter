#ifndef MAP_HPP
#define MAP_HPP

#include "Shared/QuadTree.hpp"
#include "Player.hpp"

class Map : public QuadTree<Terrain, uint16>
{
public:
    Map(std::string Name, uint64 GUID, uint16 Width, uint16 Height);

    void Update();
    void LoadObjects();
    void AddPlayer(Player* pPlayer);
    void SendToPlayers(Packet& Pckt);

    Terrain* TerrainAt(uint16 X, uint16 Y, uint16 Size);
    WorldObject* At(uint16 X, uint16 Y, uint16 Size);
    LinkedList<WorldObject>* At(Rect<uint16> Where);
    LinkedList<Terrain>* TerrainAt(Rect<uint16> Where);

    void ResetPathfinderNodes();
    uint64 GetGUID();

    void Insert(WorldObject* pObject);
private:
    QuadTree<WorldObject, uint16> Objects;
    LinkedList<Player> OnlinePlayers;
    std::string Name;
    uint64 MapGUID;
};

#endif

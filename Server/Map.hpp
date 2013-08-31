#ifndef MAP_HPP
#define MAP_HPP

#include "QuadTree.hpp"
#include "Node.hpp"
#include "Player.hpp"

class Map : public QuadTree
{
public:
    Map(std::string Name, uint64 GUID, uint16 Width, uint16 Height);

    void Update();
    void LoadObjects();
    void AddPlayer(Player* pPlayer);
    void SendToPlayers(Packet& Pckt);

    Node* TerrainAt(uint16 X, uint16 Y, uint16 Size);
    WorldObject* At(uint16 X, uint16 Y, uint16 Size); // Deprecated

    void ResetPathfinderNodes();
    uint64 GetGUID() const;
    uint32 GetEntry() const;

    void Insert(WorldObject* pObject);
private:
    void LoadTerrainData();

    LinkedList<Player> OnlinePlayers;
    std::string Name;
    uint64 MapGUID;
    uint32 Entry;
};

#endif

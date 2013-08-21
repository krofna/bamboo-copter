#ifndef MAP_HPP
#define MAP_HPP

#include "Shared/QuadTree.hpp"
#include "Player.hpp"

class Map : public QuadTree<uint32>
{
public:
    Map(std::string Name, uint64 GUID);

    void Update();
    void LoadObjects();
    void AddPlayer(Player* pPlayer);
    void SendToPlayers(Packet& Pckt);

private:
    LinkedList<Player> OnlinePlayers;
    std::string Name;
    uint64 MapGUID;
};

#endif

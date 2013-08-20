#ifndef MAP_HPP
#define MAP_HPP

#include "Shared/QuadTree.hpp"

class Map : public QuadTree<uint32>
{
public:
    Map(std::string Name, uint64 GUID);

    void Update();
    void LoadObjects();

private:
    std::string Name;
    uint64 MapGUID;
};

#endif

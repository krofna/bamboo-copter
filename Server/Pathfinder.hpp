#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "NodeQueue.hpp"
#include "Shared/Rectangle.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/utility.hpp>

class MotionMaster;
class Map;

/*
 * Todo: Implement A* heuristics
 * */
class Pathfinder : private boost::noncopyable
{
public:
    Pathfinder(boost::asio::io_service& io);
    void Enqueue(MotionMaster* pMotionMaster, sf::Vector2<uint16> Target);

private:
    struct Work
    {
        MotionMaster* pMotionMaster;
        Rect<uint16> Origin; // TODO: pMotionMaster->pMe->GetPos
        sf::Vector2<uint16> Target;
    };

    void GeneratePath(Work* pWork);
    void Relax(Node* pFirst, uint16 x, uint16 y, uint16 size, uint16 Cost);
    Map* pMap;

    /* 1)
     * OLDWHITE  OLDGRAY   OLDBLACK  <-- WHITE |GRAY  BLACK ...
     * 0,        1,        2,        <-- WHITE |3,    4,    ...
    */
    uint16 GRAY, BLACK;
    NodeQueue OpenList;
    boost::asio::io_service& io;
};

extern Pathfinder* sPathfinder;

#endif

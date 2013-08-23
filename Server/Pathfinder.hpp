#ifndef PATHFINDER_HPP
#define PATHFINDER_HPP

#include "NodeQueue.hpp"
#include "Shared/Rectangle.hpp"
#include <queue>
#include <mutex>

class MotionMaster;
class Unit;

/*
 * Todo: Implement A* heuristics
 * */
class Pathfinder
{
public:
    Pathfinder();
    ~Pathfinder();

    void Enqueue(MotionMaster* pMotionMaster, sf::Vector2<uint16> Target);
    void ProcessAll();
    void GeneratePath();

private:
    void Relax(Node* pFirst, Node* pSecond, uint16 Cost);

    struct Work
    {
        MotionMaster* pMotionMaster;
        Rect<uint16> Origin;
        sf::Vector2<uint16> Target;
    };
    Work* pWork;
    std::queue<Work*> WorkQueue;
    std::mutex WorkMutex;
    
    /* 1)
     * OLDWHITE  OLDGRAY   OLDBLACK  <-- WHITE |GRAY  BLACK ...
     * 0,        1,        2,        <-- WHITE |3,    4,    ...
    */
    uint16 GRAY, BLACK;
    NodeQueue OpenList;
};

extern Pathfinder* sPathfinder;

#endif

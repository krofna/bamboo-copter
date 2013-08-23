#include "Pathfinder.hpp"
#include "MotionMaster.hpp"
#include "Unit.hpp"
#include "Map.hpp"
#include "Shared/Log.hpp"
#include "World.hpp"
#include <stack>

Pathfinder* sPathfinder;

const int PERFECTION_LEVEL = 8; // In pixels

Pathfinder::Pathfinder() :
GRAY(1),
BLACK(2)
{
    pWork = nullptr;
}

Pathfinder::~Pathfinder()
{
    WorkMutex.lock();
    while (!WorkQueue.empty())
    {
        pWork = WorkQueue.front();
        WorkQueue.pop();
        delete pWork;
    }
    WorkMutex.unlock();
}

void Pathfinder::Enqueue(MotionMaster* pMotionMaster, sf::Vector2<uint16> Target)
{
    Work* pJob = new Work;
    pJob->pMotionMaster = pMotionMaster;
    pJob->Origin = pMotionMaster->pMe->GetRect();
    pJob->Target = Target;
    WorkMutex.lock();
    WorkQueue.push(pJob);
    WorkMutex.unlock();
}

void Pathfinder::ProcessAll()
{
    while (!WorkQueue.empty())
    {
        WorkMutex.lock();
        pWork = WorkQueue.front();
        WorkQueue.pop();
        WorkMutex.unlock();
        GeneratePath();
        delete pWork;
    }
}

void Pathfinder::Relax(Node* pFirst, Node* pSecond, uint16 Cost)
{
    if (!pSecond)
        return;

    delete pSecond;

    if (pSecond->Color < GRAY || pSecond->Cost > pFirst->Cost + Cost)
    {
        pSecond->Cost = pFirst->Cost + Cost;
        pSecond->pParent = pFirst;

        if (pSecond->Color < GRAY) // < GRAY means WHITE
        {
            pSecond->Color = GRAY;
            OpenList.Insert(pSecond);
        }
        else if (pSecond->Color == GRAY)
        {
            OpenList.DecreaseKey(pSecond->i);
        }
    }
}

void Pathfinder::GeneratePath()
{
    std::stack<sf::Vector2<uint16> >* pPath = new std::stack<sf::Vector2<uint16> >;

    Map* pMap = pWork->pMotionMaster->pMe->GetMap();

    if (GRAY == 0xFFFF)
        sWorld->ResetPathfinderNodes();

    GRAY += 2;
    BLACK += 2;

    Node* pCurrent = pMap->TerrainAt(pWork->Origin.left / PERFECTION_LEVEL, pWork->Origin.top / PERFECTION_LEVEL, PERFECTION_LEVEL);
    pCurrent->Color = GRAY;
    pCurrent->Cost = 0;

    OpenList.Clear();
    OpenList.Insert(pCurrent);

    while (!OpenList.Empty())
    {
        pCurrent = OpenList.ExtractMin();

        if (pCurrent->Position() == pWork->Target)
        {
            // TODO: Optimize directions instead of pixel perfect points
            // => if (prev - curr == curr - next) => same direction vector
            pPath->push(pCurrent->Position());
            while (pCurrent->pParent->pParent)
            {
                pPath->push(pCurrent->pParent->Position());
                pCurrent = pCurrent->pParent;
            }
            pWork->pMotionMaster->PathMutex.lock();
            delete pWork->pMotionMaster->pPath;
            pWork->pMotionMaster->pPath = pPath;
            pWork->pMotionMaster->PathMutex.unlock();
            return;
        }

        // Right
        Relax(pCurrent, pMap->TerrainAt(pCurrent->GetY() / PERFECTION_LEVEL, pCurrent->GetX() / PERFECTION_LEVEL + PERFECTION_LEVEL, PERFECTION_LEVEL), 10);
        // Low
        Relax(pCurrent, pMap->TerrainAt(pCurrent->GetY() / PERFECTION_LEVEL + PERFECTION_LEVEL, pCurrent->GetX(), PERFECTION_LEVEL), 10);
        // Right-low
        Relax(pCurrent, pMap->TerrainAt(pCurrent->GetY() / PERFECTION_LEVEL + PERFECTION_LEVEL, pCurrent->GetX() / PERFECTION_LEVEL + PERFECTION_LEVEL, PERFECTION_LEVEL), 14);
        // Left
        Relax(pCurrent, pMap->TerrainAt(pCurrent->GetY() / PERFECTION_LEVEL, pCurrent->GetX() / PERFECTION_LEVEL - PERFECTION_LEVEL, PERFECTION_LEVEL), 10);
        // High
        Relax(pCurrent, pMap->TerrainAt(pCurrent->GetY() / PERFECTION_LEVEL - PERFECTION_LEVEL, pCurrent->GetX() / PERFECTION_LEVEL, PERFECTION_LEVEL), 10);
        // Left-high
        Relax(pCurrent, pMap->TerrainAt(pCurrent->GetY() / PERFECTION_LEVEL - PERFECTION_LEVEL, pCurrent->GetX() / PERFECTION_LEVEL - PERFECTION_LEVEL, PERFECTION_LEVEL), 14);
        // Left-low
        Relax(pCurrent, pMap->TerrainAt(pCurrent->GetY() / PERFECTION_LEVEL + PERFECTION_LEVEL, pCurrent->GetX() / PERFECTION_LEVEL - PERFECTION_LEVEL, PERFECTION_LEVEL), 14);
        // Right-high
        Relax(pCurrent, pMap->TerrainAt(pCurrent->GetY() / PERFECTION_LEVEL - PERFECTION_LEVEL, pCurrent->GetX() / PERFECTION_LEVEL + PERFECTION_LEVEL, PERFECTION_LEVEL), 14);

        pCurrent->Color = BLACK;
    }

    delete pPath;
    sLog.Write(LOG_INFO, "Could not generate path from (%u, %u) to (%u, %u) for unit %llu!",
               pWork->Origin.left, pWork->Origin.top, pWork->Target.x, pWork->Target.y, pWork->pMotionMaster->pMe->GetGUID());
}

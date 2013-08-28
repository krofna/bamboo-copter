#ifndef MOTION_MASTER_HPP
#define MOTION_MASTER_HPP

#include "Shared/BasicTypes.hpp"
#include <SFML/System/Vector2.hpp>
#include <mutex>
#include <stack>

class Unit;

enum MotionType
{
    MOTION_STOP         = 0,
    MOTION_MOVE_POINT   = 1,
    MOTION_CHASE        = 2
};

class MotionMaster
{
    friend class Pathfinder;
public:
    explicit MotionMaster(Unit* pMe);
    ~MotionMaster();

    void Update();
    void ClearMotionStatus();
    void MoveChase(Unit* pTarget);
    void MovePoint(sf::Vector2<uint16> Point);
    void SetPath(std::stack<sf::Vector2<uint16> >* pPath);

private:
    bool IsPathEmpty();
    sf::Vector2<uint16> PopCheckpoint();

    std::stack<sf::Vector2<uint16> >* pPath;
    std::mutex PathMutex;
    uint8 MotionStatus;
    Unit* pMe;
    Unit* pTarget;
};

#endif

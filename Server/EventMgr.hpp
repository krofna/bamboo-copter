#ifndef EVENT_MGR_HPP
#define EVENT_MGR_HPP

#include "Shared/BasicTypes.hpp"
#include "Shared/Defines.hpp"
#include <functional>
#include <map>

#define EVENT_INVALID 0xFF

struct Event
{
    std::function<void()> Callback;
    uint32 TimeLeft;
};

typedef std::map<uint8, Event> EventMap;
typedef EventMap::value_type EventVal;

class EventMgr
{
public:
    void Register(uint8 ID, std::function<void()> Callback, uint32 TimeFromNow);
    void Unregister(uint8 ID);

    void Update();

private:
    EventMap Events;
};

#endif

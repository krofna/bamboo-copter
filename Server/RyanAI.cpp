#include "CreatureAI.hpp"
#include "Shared/Log.hpp"
#include "AIFactory.hpp"
#include "EventMgr.hpp"

enum Events
{
    EVENT_TEST = 1,
    EVENT_NON_PERPETUAL = 2
};

class RyanAI : public CreatureAI
{
public:
    RyanAI(Creature* pCreature) : CreatureAI(pCreature)
    {
        sLog.Write(LOG_REQUESTED, "Loading RyanAI");
        Events.Register(EVENT_NON_PERPETUAL, std::bind(&RyanAI::NonPerpetual, this), 10000);
        Events.Register(EVENT_TEST, std::bind(&RyanAI::Test, this), 5000, true);
    }

    void Test()
    {
        sLog.Write(LOG_REQUESTED, "Event thick");
    }

    void NonPerpetual()
    {
        sLog.Write(LOG_REQUESTED, "Event!");
    }

    void UpdateAI()
    {
        Events.Update();
    }

private:
    EventMgr Events;
};

CreatureAI* CreateRyanAI(Creature* pCreature)
{
    return new RyanAI(pCreature);
}

void LoadRyanAI()
{
    AIFactory::RegisterCreatureAI("creature_ryan", &CreateRyanAI);
}

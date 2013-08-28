#include "CreatureAI.hpp"
#include "Shared/Log.hpp"
#include "AIFactory.hpp"
#include "EventMgr.hpp"

enum Events
{
    EVENT_TEST = 1
};

class RyanAI : public CreatureAI
{
public:
    RyanAI(Creature* pCreature) : CreatureAI(pCreature)
    {
        sLog.Write(LOG_REQUESTED, "Loading RyanAI");
        Events.Register(EVENT_TEST, std::bind(&RyanAI::Test, this), 5000);
    }

    void Test()
    {
        sLog.Write(LOG_REQUESTED, "Event thick");
        Events.Register(EVENT_TEST, std::bind(&RyanAI::Test, this), 5000);
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

#include "AIFactory.hpp"
#include "CreatureAI.hpp"
#include "Creature.hpp"

std::map<std::string, CreatureAI*(*)(Creature* pCreature)> AIFactory::CreatureAIRegistry;

void AIFactory::RegisterCreatureAI(const std::string& AIName, CreatureAI*(*Creator)(Creature* pCreature))
{
    CreatureAIRegistry[AIName] = Creator;
}

CreatureAI* AIFactory::CreateCreatureAI(const std::string& AIName, Creature* pCreature)
{
    if(CreatureAIRegistry.find(AIName) == CreatureAIRegistry.end())
        return new CreatureAI(pCreature);

    return CreatureAIRegistry[AIName](pCreature);
}

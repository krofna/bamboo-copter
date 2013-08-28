#ifndef AI_FACTORY_H
#define AI_FACTORY_H

#include <map>
#include <string>

class CreatureAI;
class Creature;

class AIFactory
{
public:
    static void RegisterCreatureAI(const std::string& AIName, CreatureAI*(*Creator)(Creature* pCreature));

    static CreatureAI* CreateCreatureAI(const std::string& AIName, Creature* pCreature);

private:
    static std::map<std::string, CreatureAI*(*)(Creature* pCreature)> CreatureAIRegistry;
};

#endif

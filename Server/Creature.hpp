#ifndef CREATURE_HPP
#define CREATURE_HPP

#include "Unit.hpp"

class CreatureAI;

class Creature : public Unit
{
public:
    Creature(uint64 GUID, uint32 Entry, std::string ScriptName);

private:
    CreatureAI* pAI;
};

#endif

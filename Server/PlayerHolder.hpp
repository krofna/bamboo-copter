#ifndef PLAYER_HOLDER_HPP
#define PLAYER_HOLDER_HPP

#include "Player.hpp"
#include "Shared/ObjectHolder.hpp"

template<>
class ObjectHolder<Player>
{
public:
    static void Insert(Player* pPlayer)
    {
        UsernameTable[pPlayer->GetName()] = pPlayer;
        PlayerMap[pPlayer->GetGUID()] = pPlayer;
    }

    static void Erase(Player* pPlayer)
    {
        UsernameTable.erase(pPlayer->GetName());
        PlayerMap.erase(pPlayer->GetGUID());
    }

    static Player* Find(uint64 GUID)
    {
        std::unordered_map<uint64, Player*>::iterator It = PlayerMap.find(GUID);
        return (It != PlayerMap.end()) ? It->second : nullptr;
    }

    static Player* Find(std::string const& Username)
    {
        std::unordered_map<std::string, Player*>::iterator It = UsernameTable.find(Username);
        return (It != UsernameTable.end()) ? It->second : nullptr;
    }

    template <class F>
    static void Execute(F Function)
    {
        for (auto i = PlayerMap.begin() ; i != PlayerMap.end() ; ++i)
            Function((*i).second);
    }

private:
    ObjectHolder() {}
    static std::unordered_map<std::string, Player*> UsernameTable;
    static std::unordered_map<uint64, Player*> PlayerMap;
};

#endif

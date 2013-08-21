#include "PlayerHolder.hpp"

std::unordered_map<uint64, Player*> ObjectHolder<Player>::PlayerMap;
std::unordered_map<std::string, Player*> ObjectHolder<Player>::UsernameTable;

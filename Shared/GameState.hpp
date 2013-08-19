#ifndef GAME_STATE_HPP
#define GAME_STATE_HPP

#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include "Shared/Defines.hpp"

enum
{
    STATE_LOGIN = 0,
    STATE_WORLD = 1,
    STATE_MAX   = 2
};

class GameState
{
public:
    virtual ~GameState() {}
    virtual void Draw() = 0;
    virtual void Update() = 0;
    virtual void HandleEvent(sf::Event Event) = 0;
};

#endif

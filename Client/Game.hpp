#ifndef GAME_HPP
#define GAME_HPP

#include <SFML/Graphics/RenderWindow.hpp>
#include <mutex>
#include "Shared/Stack.hpp"

class GameState;

class Game
{
public:
    Game();
    void Run();
    void PushState(GameState* pState);
    void PopState();

    sf::RenderWindow& GetWindow();

private:
    Stack<GameState*> StateStack;
    sf::RenderWindow Window;
    std::mutex StateMutex;
};

#endif

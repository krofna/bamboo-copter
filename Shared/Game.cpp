#include "Game.hpp"
#include "Shared/GameState.hpp"

Game::Game(const char* Name) :
StateStack(STATE_MAX),
Window(sf::VideoMode::getDesktopMode(), Name)
{
    Window.setFramerateLimit(65);
}

void Game::Run()
{
    sf::Clock clock;
    sf::Time elapsed = sf::Time::Zero;
    sf::Event event;
    GameState* pState = StateStack.Top();

    while (Window.isOpen())
    {
        elapsed += clock.restart();
        while (elapsed.asMilliseconds() > GAME_HEARTBEAT)
        {
            elapsed -= sf::milliseconds(GAME_HEARTBEAT);

            StateMutex.try_lock();
            pState = StateStack.Top();
            StateMutex.unlock();

            while (Window.pollEvent(event))
                pState->HandleEvent(event);
            pState->Update();
        }

        Window.clear();
        pState->Draw();
        Window.display();
    }
}

void Game::PushState(GameState* pState)
{
    std::lock_guard<std::mutex> lock(StateMutex);
    StateStack.Push(pState);
}

void Game::PopState()
{
    std::lock_guard<std::mutex> lock(StateMutex);
    StateStack.Pop();
}

sf::RenderWindow& Game::GetWindow()
{
    return Window;
}

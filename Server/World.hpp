#ifndef WORLD_HPP
#define WORLD_HPP

#include "Map.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>

class World : private LinkedList<Map>
{
public:
    World(boost::asio::io_service& io);
    ~World();

    void Load();
    void Run();
    void Update();

    void ResetPathfinderNodes();
private:
    boost::asio::deadline_timer UpdateTimer;
    boost::asio::io_service& io;
};

extern World* sWorld;

#endif

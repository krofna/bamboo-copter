#ifndef WORLD_HPP
#define WORLD_HPP

#include "Shared/BasicTypes.hpp"
#include <boost/asio/io_service.hpp>
#include <boost/asio/deadline_timer.hpp>

class World
{
public:
    World(boost::asio::io_service& io);

    void Load();
    void Run();
    void Update();

private:
    boost::asio::deadline_timer UpdateTimer;
    boost::asio::io_service& io;
};

#endif

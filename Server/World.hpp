#ifndef WORLD_HPP
#define WORLD_HPP

#include "Shared/BasicTypes.hpp"
#include <boost/asio/io_service.hpp>
#include <chrono>

class World
{
public:
    World(boost::asio::io_service& io);

    void Run();
    void Update(std::chrono::milliseconds diff);

private:
    boost::asio::io_service& io;
};

#endif

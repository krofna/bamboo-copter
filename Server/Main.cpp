#include "World.hpp"
#include "WorldAcceptor.hpp"
#include <boost/make_shared.hpp>

int main(int argc, char** argv)
{
    boost::asio::io_service io;

    boost::shared_ptr<WorldAcceptor> pAcceptor = boost::make_shared<WorldAcceptor>(io);
    sWorld = new World(io);
    pAcceptor->Accept();
    sWorld->Load();
    io.run();

    delete sWorld;
    return 0;
}

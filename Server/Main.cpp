#include "World.hpp"
#include "WorldAcceptor.hpp"
#include "Shared/File.hpp"
#include <boost/make_shared.hpp>

void GenDummyTemplateFile()
{
    File f("../Shared/CreatureTemplate.tem", std::ios::out);
    f << (uint8)CREATURE_TEMPLATE << (uint32)0 << "creature_ryan";
    f.Close();
}

int main(int argc, char** argv)
{
    GenDummyTemplateFile();

    boost::asio::io_service io;

    boost::shared_ptr<WorldAcceptor> pAcceptor = boost::make_shared<WorldAcceptor>(io);
    sWorld = new World(io);
    pAcceptor->Accept();
    sWorld->Load();
    io.run();

    delete sWorld;
    return 0;
}

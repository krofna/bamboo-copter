#include "Shared/File.hpp"
#include "Shared/BasicTypes.hpp"
#include "Shared/Templates.hpp"

void GenDummyMap()
{
    File t("../Shared/TerrainTemplate.tem", std::ios::out);
    t << (uint8)TERRAIN_TEMPLATE << (uint32)0 << std::string("test.png") << (uint16)0 << (uint16)0 << (uint16)64 << (uint16)64;
    t.Close();

    File f("../Shared/TestMap.map", std::ios::out);
    f << (uint32)0 << (uint16)0 << (uint16)0 << (uint16)0 << uint16(1024) << uint16(1024);
    f.Close();
}

int main(int argc, char** argv)
{
    GenDummyMap();
    return 0;
}

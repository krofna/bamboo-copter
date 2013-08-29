#ifndef TEMPLATES_HPP
#define TEMPLATES_HPP

#include <vector>
#include <SFML/System/Vector2.hpp>
#include "Shared/BasicTypes.hpp"

namespace sf
{
    class Texture;
}

enum TemplateType
{
    NULL_TEMPLATE       = 0x0,
    ANIMATION_TEMPLATE  = 0x1,
    CREATURE_TEMPLATE   = 0x2,
    TERRAIN_TEMPLATE    = 0x3,
    MAP_TEMPLATE        = 0x4 // TODO
};

struct Template
{
    uint32 Entry;
};

struct SpriteTemplate : Template
{
    sf::Texture* pTexture;
    sf::Vector2<uint16> Size;
};

struct CAnimationTemplate : SpriteTemplate
{
    std::vector<std::vector<sf::Vector2<uint16>>> TexPos;
    std::vector<uint8> FramesPerAnim;
};

struct TerrainTemplate : SpriteTemplate
{
    sf::Vector2<uint16> TexPos;
};

struct WorldObjectTemplate : Template
{
};

struct UnitTemplate : WorldObjectTemplate
{
};

struct HeroTemplate : UnitTemplate
{
};

struct CreatureTemplate : UnitTemplate
{
    std::string ScriptName;
};

#endif

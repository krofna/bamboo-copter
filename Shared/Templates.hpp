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
    ANIMATION_TEMPLATE  = 0x1
};

struct CAnimationTemplate
{
    sf::Texture* pTexture;
    std::vector<std::vector<sf::Vector2<uint16>>> TexPos;
    std::vector<uint8> FramesPerAnim;
    uint32 Entry;
};

struct SAnimationTemplate
{
    std::string Texture;
    char* Data;
    uint32 Entry;
};

#endif

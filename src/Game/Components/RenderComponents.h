#ifndef RENDERCOMPONENTS_H
#define RENDERCOMPONENTS_H

#include <string>

// Interface for both SpriteComponent and TextComponent, as they will be rendered by same System
// Hmmm but system does not exactly allow for this... assuming they have different z-indexes...

// TODO: could maybe have like a "RenderComponent" with just a z-index
// And then SpriteComponent and TextComponent inheret from that, allows render component to just require Has<RenderCompoennt>
struct SpriteComponent {
    std::string filepath;
    int zIndex;

    SpriteComponent(std::string filepath = "", int zIndex = 0)
    {
        this->filepath = filepath;
        this->zIndex = zIndex;
    }
};

#endif // RENDERCOMPONENTS_H
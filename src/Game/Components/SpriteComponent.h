#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>

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

#endif // SPRITECOMPONENT_H
#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>

struct SpriteComponent {
    std::string filepath;

    SpriteComponent(std::string filepath = "")
    {
        this->filepath = filepath;
    }
};

#endif // SPRITECOMPONENT_H
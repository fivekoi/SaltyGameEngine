#ifndef ENGINESPRITECOMPONENT_H
#define ENGINESPRITECOMPONENT_H

#include <string>

struct EngineSpriteComponent {
    std::string filepath;

    EngineSpriteComponent(std::string filepath = "")
    {
        this->filepath = filepath;
    }
};

#endif // ENGINESPRITECOMPONENT_H
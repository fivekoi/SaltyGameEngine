#ifndef ENGINESPRITECOMPONENT_H
#define ENGINESPRITECOMPONENT_H

#include <string>

// Engine will handle texture asset management, so no need for proxy class like in Game's SpriteComponent
struct EngineSpriteComponent {
    std::string filepath;
    
    EngineSpriteComponent(std::string filepath = "")
    {
        this->filepath = filepath;
    }
};

#endif // ENGINESPRITECOMPONENT_H
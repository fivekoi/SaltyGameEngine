#ifndef TRANSFORMCOMPONENT_H
#define TRANSFORMCOMPONENT_H

#include <glm.hpp>


struct TransformComponent {
    glm::vec2 position;
    glm::vec2 scale;
    float rotation;
    int zindex; 
    // TODO: zindex should be a proxy, and we will reference whatever renderer is being used

    TransformComponent(glm::vec2 position = glm::vec2(0,0), glm::vec2 scale = glm::vec2(1, 1), float rotation = 0.0, float zindex = 0)
    {
        this->position = position;
        this->scale = scale;
        this->rotation = rotation;
        this->zindex = zindex;
    }
};

#endif // TRANSFORMCOMPONENT_H
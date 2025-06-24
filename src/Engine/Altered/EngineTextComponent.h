#ifndef ENGINETEXTCOMPONENT_H
#define ENGINETEXTCOMPONENT_H

#include <string>

#include <SDL.h>
#include <glm.hpp>

struct EngineTextComponent {
    std::string filepath;
    std::string text;
    int fontSize;
    SDL_Color color;

    EngineTextComponent(std::string filepath = "", std::string text = "", int fontSize = 8, const SDL_Color color = {0, 0, 0, 255})
    {
        this->filepath = filepath;
        this->text = text;
        this->fontSize = fontSize;
        this->color = color;
    }
};

#endif // ENGINETEXTCOMPONENT_H
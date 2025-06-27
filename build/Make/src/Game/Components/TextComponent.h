#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include <string>

#include <SDL.h>
#include <glm.hpp>

struct TextComponent {
    std::string filepath;
    std::string text;
    int fontSize;
    SDL_Color color;

    // TODO: consider adding a bool "DontUnloadOnChange"
    // If the text will cycle between a few set strings then should set to true, otherwise defaults to false...?
    TextComponent(std::string filepath = "", std::string text = "", int fontSize = 8, const SDL_Color& color = {0, 0, 0, 1})
    {
        this->filepath = filepath;
        this->text = text;
        this->fontSize = fontSize;
        this->color = color;
    }
};

#endif // TEXTCOMPONENT_H
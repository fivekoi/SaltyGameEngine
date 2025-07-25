#ifndef ASSETDATA_H
#define ASSETDATA_H

#include <SDL.h>
#include <SDL_ttf.h>
#include <glm.hpp>

struct TextureData {
    SDL_Texture* texture;
    glm::ivec2 textureSize;
    int refCount;

    TextureData() = default;
    TextureData(SDL_Texture* texture, glm::ivec2 textureSize, int refCount)
    : texture(texture), textureSize(textureSize), refCount(refCount) {};
};

struct FontData {
    TTF_Font* font;
    int refCount;

    FontData() = default;
    FontData(TTF_Font* font, int refCount)
    : font(font), refCount(refCount) {};
};

#endif
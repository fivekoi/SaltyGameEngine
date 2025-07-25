#ifndef ASSETMANAGER_H
#define ASSETMANAGER_H

#include <map>
#include <memory>
#include <string>
#include <unordered_map>

#include <SDL.h>
#include <SDL_ttf.h>
#include <glm.hpp>

#include "Game/AssetManager/AssetData.h"

class AssetManager {
private:
    SDL_Renderer* renderer;

    std::unordered_map<std::string, TextureData> textures;
    // TODO: might have seperate font system later (with textures already made)
    std::map<std::string, TTF_Font*> fonts;

public:
    AssetManager(SDL_Renderer* renderer)
    : renderer(renderer) {};
    ~AssetManager();

    void ClearAssets();

    void AddTexture(const std::string& filepath);
    TextureData GetTexture(const std::string& filepath);

    void AddFont(const std::string& filepath, int fontSize);
    TTF_Font* GetFont(const std::string& filepath);
};

#endif // ASSETMANAGER_H
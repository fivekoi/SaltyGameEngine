#include "Engine/Altered/EngineAssetManager.h"

#include <iostream>
#include <utility>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <glm.hpp>

EngineAssetManager::~EngineAssetManager() { ClearAssets(); }

void EngineAssetManager::ClearAssets()
{
    for(const auto& kv : textures)
    { SDL_DestroyTexture(kv.second.texture); }
    textures.clear();

    for(auto kv : fonts)
    { TTF_CloseFont(kv.second.font); }
    fonts.clear();
}

void EngineAssetManager::AddTexture(const std::string& filepath)
{
    if(!textures.count(filepath))
    {
        // TODO: should check that filepath is valid, just log some error here, should never happen but who knows
        SDL_Surface* surface = IMG_Load(("Projects/" + engineData->projectName + "/Unique/Assets/" + filepath).c_str());
        // Check if !surface for failure
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        SDL_Point sdlSize;
        SDL_QueryTexture(texture, NULL, NULL, &sdlSize.x, &sdlSize.y);
        glm::ivec2 size = glm::ivec2(sdlSize.x, sdlSize.y);

        textures.emplace(filepath, TextureData(texture, size, 1));
    }
    else{
        // Increment refCount of texture at filepath
        textures[filepath].refCount++;
    }
}

TextureData EngineAssetManager::GetTexture(const std::string& filepath)
{
    // TODO: add this back once i add drag and drop (also count out default "")
    // assert(textures.count(filepath));
    return textures[filepath];
}


void EngineAssetManager::AddFont(const std::string& filepath, int fontSize){
    std::pair<std::string, int> key = std::make_pair(filepath, fontSize);
    if(fonts.count(key)){
        fonts[key].refCount++;
    }
    else {
        fonts.emplace(std::pair<std::string, int>(filepath, fontSize), 
            FontData(TTF_OpenFont(("Projects/" + engineData->projectName + "/Unique/Assets/" + filepath).c_str(), fontSize), 1));
    }
}

TTF_Font* EngineAssetManager::GetFont(const std::string& filepath, int fontSize){
    // assert(fonts.count(filepath));
    return fonts[std::pair<std::string, int>(filepath, fontSize)].font;
}

void EngineAssetManager::RemoveFont(const std::string& filepath, int fontSize){
    std::pair<std::string, int> key = std::make_pair(filepath, fontSize);
    if(--fonts[key].refCount <= 0){
        TTF_CloseFont(fonts[key].font);
        fonts.erase(key);
    }
}

void EngineAssetManager::AddFontTexture(const std::string& filepath, int fontSize, const std::string& text, SDL_Color color){
    FontTextureKey ftk = FontTextureKey(filepath, fontSize, text, color);
    if(fontTextures.count(ftk)){
        fontTextures[ftk].refCount++;
    }
    else {
        TTF_Font* font = GetFont(filepath, fontSize);
    
        SDL_Surface* surface = TTF_RenderText_Solid(font, text.c_str(), color);
        SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
        SDL_FreeSurface(surface);

        glm::ivec2 size;
        TTF_SizeText(font, text.c_str(), &size.x, &size.y);

        fontTextures.emplace(ftk, TextureData(texture, size, 1));
    }
}

TextureData EngineAssetManager::GetFontTexture(const std::string& filepath, int fontSize, const std::string& text, SDL_Color color)
{
    return fontTextures[FontTextureKey(filepath, fontSize, text, color)];
}

void EngineAssetManager::RemoveFontTexture(const std::string& filepath, int fontSize, const std::string& text, SDL_Color color){
    FontTextureKey ftk = FontTextureKey(filepath, fontSize, text, color);
    if(--fontTextures[ftk].refCount <= 0){
        SDL_DestroyTexture(fontTextures[ftk].texture);
        fontTextures.erase(ftk);
    }
}
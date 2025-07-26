#include "Game/AssetManager/AssetManager.h"

#include <iostream>

#include <SDL_image.h>
#include <SDL_ttf.h>
#include <glm.hpp>

AssetManager::~AssetManager() { ClearAssets(); }

void AssetManager::ClearAssets()
{
    for(const auto& kv : textures)
    { SDL_DestroyTexture(kv.second.texture); }
    textures.clear();

    for(auto kv : fonts)
    { TTF_CloseFont(kv.second.font); }
    fonts.clear();

    for(auto kv : fontTextures)
    { SDL_DestroyTexture(kv.second.texture); }
    fontTextures.clear();
}

void AssetManager::AddTexture(const std::string& filepath)
{
    if(!textures.count(filepath))
    {
        // TODO: need to check that filepath is valid, just log some error here, should never happen but who knows
        SDL_Surface* surface = IMG_Load(("Unique/Assets/" + filepath).c_str());
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

TextureData AssetManager::GetTexture(const std::string& filepath)
{
    // TODO: add this back once i add drag and drop (also count out default "")
    // assert(textures.count(filepath));
    return textures[filepath];
}


void AssetManager::AddFont(const std::string& filepath, int fontSize){
    std::cout << filepath << ' ' << fontSize << '\n';

    std::pair<std::string, int> key = std::make_pair(filepath, fontSize);
    if(fonts.count(key)){
        fonts[key].refCount++;
    }
    else {
        fonts.emplace(std::pair<std::string, int>(filepath, fontSize), 
            FontData(TTF_OpenFont(("Unique/Assets/" + filepath).c_str(), fontSize), 1));
    }
}

TTF_Font* AssetManager::GetFont(const std::string& filepath, int fontSize){
    // assert(fonts.count(filepath));
    return fonts[std::pair<std::string, int>(filepath, fontSize)].font;
}

void AssetManager::RemoveFont(const std::string& filepath, int fontSize){
    std::pair<std::string, int> key = std::make_pair(filepath, fontSize);
    if(--fonts[key].refCount <= 0){
        TTF_CloseFont(fonts[key].font);
        fonts.erase(key);
    }
}

void AssetManager::AddFontTexture(const std::string& filepath, int fontSize, const std::string& text, SDL_Color color){
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

TextureData AssetManager::GetFontTexture(const std::string& filepath, int fontSize, const std::string& text, SDL_Color color)
{
    return fontTextures[FontTextureKey(filepath, fontSize, text, color)];
}

void AssetManager::RemoveFontTexture(const std::string& filepath, int fontSize, const std::string& text, SDL_Color color){
    FontTextureKey ftk = FontTextureKey(filepath, fontSize, text, color);
    if(--fontTextures[ftk].refCount <= 0){
        SDL_DestroyTexture(fontTextures[ftk].texture);
        fontTextures.erase(ftk);
    }
}
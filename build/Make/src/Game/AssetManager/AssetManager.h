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
    
    // (filepath, fontSize) -> TTF_Font
    std::map<std::pair<std::string, int>, FontData> fonts;
    
    struct FontTextureKey {
        FontTextureKey(std::string filepath, int fontSize, std::string text, SDL_Color color)
        : filepath(filepath), fontSize(fontSize), text(text), color(color) {};
        
        std::string filepath;
        int fontSize;
        std::string text;
        SDL_Color color;

        bool operator<(FontTextureKey other) const {
            if(other.filepath != filepath) return filepath < other.filepath;
            if(other.fontSize != fontSize) return fontSize < other.fontSize;
            if(other.text != text) return text < other.text;

            if(other.color.r != color.r) return color.r < other.color.r;
            if(other.color.g != color.g) return color.g < other.color.g;
            if(other.color.b != color.b) return color.b < other.color.b;
            if(other.color.a != color.a) return color.a < other.color.a;
            return false;
        }
    };
    // TODO: also, should these be unordered_maps? might be faster (but requires a hash...)
    std::map<FontTextureKey, TextureData> fontTextures;

public:
    AssetManager(SDL_Renderer* renderer)
    : renderer(renderer) {};
    ~AssetManager();

    void ClearAssets();

    void AddTexture(const std::string& filepath);
    TextureData GetTexture(const std::string& filepath);

    // TODO: i kinda wanna add a removeTexture actually for sprites too...
    // might as well minimize memory even in the engine (cant see why people would be switching sprites too often back and forth)
    // plus they cant do it that fast by hand anyways

    void AddFont(const std::string& filepath, int fontSize);
    TTF_Font* GetFont(const std::string& filepath, int fontSize);
    void RemoveFont(const std::string& filepath, int fontSize);
    void AddFontTexture(const std::string& filepath, int fontSize, const std::string& text, SDL_Color color);
    TextureData GetFontTexture(const std::string& filepath, int fontSize, const std::string& text, SDL_Color color);
    void RemoveFontTexture(const std::string& filepath, int fontSize, const std::string& text, SDL_Color color);
};

#endif // ASSETMANAGER_H
#ifndef ENGINEASSETMANAGER_H
#define ENGINEASSETMANAGER_H

#include <map>
#include <memory>
#include <string>

#include <SDL.h>
#include <SDL_ttf.h>
#include <glm.hpp>

#include "Engine/EngineData.h"

class EngineAssetManager {
private:
    SDL_Renderer* renderer;

    std::map<std::string, SDL_Texture*> textures; // TODO: could probably combine these two into one map, so we dont need to double access
    std::map<std::string, glm::vec2> textureSizes; // two
    
    // From (filepath, fontSize) -> TTF_Font
    std::map<std::pair<std::string, int>, TTF_Font*> fonts;
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
    std::map<FontTextureKey, SDL_Texture*> fontTextures; // TODO: could probably combine these two into one map
    std::map<FontTextureKey, glm::ivec2> fontTextureSizes; // two

    std::shared_ptr<EngineData> engineData;
public:
    EngineAssetManager(SDL_Renderer* renderer, std::shared_ptr<EngineData> engineData)
    : renderer(renderer), engineData(engineData) {};
    ~EngineAssetManager();

    void ClearAssets();

    void AddTexture(const std::string& filepath);
    SDL_Texture* GetTexture(const std::string& filepath);
    glm::vec2 GetTextureSize(const std::string& filepath);

    void AddFont(const std::string& filepath, int fontSize);
    TTF_Font* GetFont(const std::string& filepath, int fontSize);
    void CreateFontTexture(const std::string& filepath, int fontSize, const std::string& text, SDL_Color color);
    SDL_Texture* GetFontTexture(const std::string& filepath, int fontSize, const std::string& text, SDL_Color color);
    glm::ivec2 GetFontTextureSize(const std::string& filepath, int fontSize, const std::string& text, SDL_Color color);
};

#endif // ENGINEASSETMANAGER_H
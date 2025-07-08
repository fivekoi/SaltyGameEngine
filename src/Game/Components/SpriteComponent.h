#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>
#include "Game/AssetManager/AssetManager.h"

class SpriteComponent {
private:
    std::shared_ptr<AssetManager> assetManager;

    // Proxy class for managing sprite textures
    class PFilepath {
    private:
        std::string filepath;
        SpriteComponent* component;
    public:
        PFilepath(SpriteComponent* component, std::string filepath = "")
        : component(component), filepath(filepath) {}

        // Overload assignment operator
        PFilepath& operator=(std::string newFilepath){
            if (filepath != newFilepath){
                component->OnFilepathChanged(filepath, newFilepath);
                filepath = newFilepath;
            }
            return *this;
        }

        // Implicit conversion to int
        operator std::string() const {
            return filepath;
        }
    };

    void OnFilepathChanged(std::string prevFilepath, std::string newFilepath){
        // TODO: also remove previous texture?
        assetManager->AddTexture(filepath);
    }
public:
    SpriteComponent(std::string filepath = "")
    {
        this->filepath = filepath;
    }

    PFilepath filepath = PFilepath(this, "");

    // FOR ENGINE USE ONLY, assigned by RenderSystem on AddComponent(ToSystem)
    void SetAssetManager(std::shared_ptr<AssetManager> assetManager) {
        this->assetManager = assetManager;
    }
};

#endif // SPRITECOMPONENT_H
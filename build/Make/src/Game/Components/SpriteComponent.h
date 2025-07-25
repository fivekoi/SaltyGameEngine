#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <iostream>
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
        PFilepath& operator=(const std::string& newFilepath){
            if (filepath != newFilepath){
                component->OnFilepathChanged(filepath, newFilepath);
                filepath = newFilepath;
            }
            return *this;
        }



        // Implicit conversion to string
        operator std::string() const {
            return filepath;
        }

        // Set filepath without calling the updater function, built for use by engine - not users
        void ManuallySet(std::string newFilepath){
            filepath = newFilepath;
        }
    };

    void OnFilepathChanged(std::string prevFilepath, std::string newFilepath){
        // TODO: also remove previous texture?
        if(assetManager){
            assetManager->AddTexture(newFilepath);
        }
    }
public:
    SpriteComponent(std::string filepath = "")
    {
        this->filepath.ManuallySet(filepath);
    }

    PFilepath filepath = PFilepath(this, "");

    // FOR ENGINE USE ONLY, assigned by RenderSystem on AddComponent(ToSystem)
    void SetAssetManager(std::shared_ptr<AssetManager> assetManager) {
        this->assetManager = assetManager;
    }

    // // Copy constructor
    // SpriteComponent(const SpriteComponent& other)
    // : assetManager(other.assetManager)
    // {
    //     this->filepath.ManuallySet(other.filepath);
    // }

    // Copy assignment - when resizing component pool we need to preserve assetManager
    SpriteComponent& operator=(const SpriteComponent& other){
        if(this != &other) {
            assetManager = other.assetManager;
            filepath.ManuallySet(other.filepath);
        }
        return *this;
    }
};

#endif // SPRITECOMPONENT_H
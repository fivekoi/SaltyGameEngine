#ifndef SPRITECOMPONENT_H
#define SPRITECOMPONENT_H

#include <string>

class SpriteComponent {
private:
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
        // Call instance of asset manager
    }
public:
    SpriteComponent(std::string filepath = "")
    {
        this->filepath = filepath;
    }

    PFilepath filepath = PFilepath(this, "");
};

#endif // SPRITECOMPONENT_H
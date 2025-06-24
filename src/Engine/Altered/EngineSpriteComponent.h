#ifndef ENGINESPRITECOMPONENT_H
#define ENGINESPRITECOMPONENT_H

#include <string>

#include <iostream>

class EngineSpriteComponent {
private:
    // Proxy class for managing sprite textures
    class PFilepath {
    private:
        std::string filepath;
        EngineSpriteComponent* component;
    public:
        PFilepath(EngineSpriteComponent* component, std::string filepath = "")
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
        std::cout << prevFilepath << ' ' << newFilepath << '\n';
    }
public:
    EngineSpriteComponent(std::string filepath = "")
    {
        this->filepath = filepath;
    }

    PFilepath filepath = PFilepath(this, "");
};

#endif // ENGINESPRITECOMPONENT_H
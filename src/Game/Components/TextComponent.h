#ifndef TEXTCOMPONENT_H
#define TEXTCOMPONENT_H

#include <iostream>
#include <string>

#include <SDL.h>
#include <glm.hpp>

class TextComponent {
private:
    std::shared_ptr<AssetManager> assetManager;

    // Proxy class for managing filepath
    class PFilepath {
    private:
        std::string filepath;
        TextComponent* component;
    public:
        PFilepath(TextComponent* component, std::string filepath = "")
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
        assetManager->RemoveFont(prevFilepath, fontSize);
        assetManager->RemoveFontTexture(prevFilepath, fontSize, text, color);

        assetManager->AddFont(newFilepath, fontSize);
        assetManager->AddFontTexture(newFilepath, fontSize, text, color);
    }

    // Proxy class for managing fontSize
    class PFontSize {
    private:
        int fontSize;
        TextComponent* component;
    public:
        PFontSize(TextComponent* component, int fontSize = 0)
        : component(component), fontSize(fontSize) {}

        // Overload assignment operator
        PFontSize& operator=(int newFontSize){
            if (fontSize != newFontSize){
                component->OnFontSizeChanged(fontSize, newFontSize);
                fontSize = newFontSize;
            }
            return *this;
        }

        // Set fontSize without calling the updater function, built for use by engine - not users
        void ManuallySet(int newFontSize){
            fontSize = newFontSize;
        }

        // Implicit conversion to int
        operator int() const {
            return fontSize;
        }
    };
    void OnFontSizeChanged(int prevFontSize, int newFontSize){
        assetManager->RemoveFont(filepath, prevFontSize);
        assetManager->RemoveFontTexture(filepath, prevFontSize, text, color);

        assetManager->AddFont(filepath, newFontSize);
        assetManager->AddFontTexture(filepath, newFontSize, text, color);
    }
    

    // Proxy class for managing font text 
    class PText {
    private:
        std::string text;
        TextComponent* component;
    public:
        PText(TextComponent* component, std::string text = "")
        : component(component), text(text) {}

        // Overload assignment operator
        PText& operator=(const std::string& newText){
            if (text != newText){
                component->OnTextChanged(text, newText);
                text = newText;
            }
            return *this;
        }

        // Implicit conversion to string
        operator std::string() const {
            return text;
        }

        // Set filepath without calling the updater function, built for use by engine - not users
        void ManuallySet(std::string newText){
            text = newText;
        }
    };
    void OnTextChanged(std::string prevText, std::string newText){
        assetManager->RemoveFontTexture(filepath, fontSize, prevText, color);

        assetManager->AddFontTexture(filepath, fontSize, newText, color);
    }

    // Proxy class for managing color
    class PColor {
    private:
        SDL_Color color;
        TextComponent* component;
    public:
        PColor(TextComponent* component, SDL_Color color = {0, 0, 0, 255})
        : component(component), color(color) {}

        // Overload assignment operator
        PColor& operator=(const SDL_Color& newColor){
            if (color.r != newColor.r || color.g != newColor.g || color.b != newColor.b || color.a != newColor.a){
                component->OnColorChanged(color, newColor);
                color = newColor;
            }
            return *this;
        }
        // NOTE: alpha value is optional
        PColor& operator=(std::initializer_list<int> rgba) {
            if(rgba.size() >= 3) {
                glm::ivec4 newColor;
                newColor[3] = color.a;
                
                int i = 0;
                for (auto value : rgba){
                    newColor[i] = value;
                    i += 1;
                    if(i >= 4) 
                    { break; }
                }

                SDL_Color newSDLColor = {static_cast<Uint8>(newColor[0]), static_cast<Uint8>(newColor[1]), 
                                         static_cast<Uint8>(newColor[2]), static_cast<Uint8>(newColor[3])};
                if (color.r != newColor.r || color.g != newColor.g || color.b != newColor.b || color.a != newColor.a){
                    component->OnColorChanged(color, newSDLColor);
                    color = newSDLColor;
                }
            }
            return *this;
        }


        // Implicit conversion to SDL_Color
        operator SDL_Color() const {
            return color;
        }

        // Set filepath without calling the updater function, built for use by engine - not users
        void ManuallySet(SDL_Color newColor){
            color = newColor;
        }
    };
    void OnColorChanged(SDL_Color prevColor, SDL_Color newColor){
        assetManager->RemoveFontTexture(filepath, fontSize, text, prevColor);
        
        assetManager->AddFontTexture(filepath, fontSize, text, newColor);
    }

public:
    // TODO: consider adding a bool "DontUnloadOnChange"
    // If the text will cycle between a few set strings then should set to true, otherwise defaults to false...?
    TextComponent(std::string filepath = "", std::string text = "", int fontSize = 8, const SDL_Color& color = {0, 0, 0, 255})
    {
        this->filepath.ManuallySet(filepath);
        this->text.ManuallySet(text);
        this->fontSize.ManuallySet(fontSize);
        this->color.ManuallySet(color);
    }

    PFilepath filepath = PFilepath(this);
    PText text = PText(this);
    PFontSize fontSize = PFontSize(this);
    PColor color = PColor(this);

    // FOR ENGINE USE ONLY, assigned by RenderSystem on AddComponent(ToSystem)
    void SetAssetManager(std::shared_ptr<AssetManager> assetManager) {
        this->assetManager = assetManager;
    }

    TextComponent& operator=(const TextComponent& other){
        if(this != &other) {
            assetManager = other.assetManager;
            filepath.ManuallySet(other.filepath);
            text.ManuallySet(other.text);
            fontSize.ManuallySet(other.fontSize);
            color.ManuallySet(other.color);
        }
        return *this;
    }
};

#endif // TEXTCOMPONENT_H
#ifndef GAME_H
#define GAME_H

#include <memory>
#include <vector>

#include <SDL.h>
#include <json.hpp>
using json = nlohmann::json;

#include "Game/ECS/ECS.h"
#include "Game/AssetManager/AssetManager.h"
#include "Game/Salty/SaltyAudio.h"
#include "Game/Salty/SaltyTypes.h"

class Game {
    private:
        SDL_Window* window;
        int width, height;
        // Viewport dims `div` Camera::aspectRatio
        int scale;
        SDL_Renderer* renderer;

        std::unique_ptr<Registry> registry; 
        std::shared_ptr<AssetManager> assetManager;

        // In ms
        uint64_t targetFrameTime = 8;

        void CreateEntityTree(json jEntities, json jRootIds);
        SaltyType CreateArg(json jType, json jVal);
    public:
        Game();
        ~Game();
        int Initialize();
        void LoadScene(int sceneIndex);
        void Run();
        void ProcessInput();
        // deltaTime converted into seconds here
        void Update(float deltaTime);
        void Render();
        void Destroy();

        bool isRunning; 
        uint64_t prevFrameTime;
};


#endif // GAME_H
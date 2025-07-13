#ifndef RENDERSYSTEM_H
#define RENDERSYSTEM_H

#include <algorithm>
#include <iostream>

#include <SDL.h>

#include "Game/ECS/ECS.h"
#include "Game/Components/TransformComponent.h"
#include "Game/Components/SpriteComponent.h"
#include "Game/Components/TextComponent.h"
#include "Game/AssetManager/AssetManager.h"
#include "Game/Salty/SaltyCamera.h"

class RenderSystem : public System {
private: 
    std::vector<Entity> entities;

    std::shared_ptr<AssetManager> assetManager;

public:
    RenderSystem(std::shared_ptr<AssetManager> assetManager) 
    : assetManager(assetManager) {};

    bool CheckEntity(Entity entity) override
    {
        bool hasSprite = entity.HasComponent<SpriteComponent>();
        bool hasText = entity.HasComponent<TextComponent>();
        if(hasSprite){
            entity.GetComponent<SpriteComponent>().SetAssetManager(assetManager);
        }
        if(hasText){
            entity.GetComponent<TextComponent>().SetAssetManager(assetManager);
        }

        return hasSprite || hasText;
    }

    void AddEntityToSystem(Entity entity) override
    {
        int zindex = entity.GetComponent<TransformComponent>().zindex;
        int id = entity.GetId();
        
        std::vector<Entity>::iterator it = entities.begin();
        while(it != entities.end() && id != it->GetId() && it->GetComponent<TransformComponent>().zindex <= zindex){
            ++it;
        }
        if(it == entities.end() || id != it->GetId()) // Handles the duplicate protection
        { entities.insert(it, entity); }
    }

    // Removes first elem of entities with same Id as entity
    void RemoveEntityFromSystem(Entity entity, bool dontCheck) override
    {
        //TODO figure out better looking implementation
        /*
        int i = 0;
        // I: entity NOT IN entities[0..i) 
        // V: entities.size() - i
        while(i < entities.size() && entities[i] != entity)
        { i++; }

        entities.erase(entities.begin()+i);
        */
        if(dontCheck || !CheckEntity(entity))
        { 
            entities.erase(std::remove_if(entities.begin(), entities.end(), [&entity](Entity other) {
            return entity == other;
                }), entities.end()); // Erase-remove idiom
        }
    }

    // TODO: should maybe get rid of these other two as well...
    void Update(SDL_Renderer* renderer, int viewportScale)
    {
        // Camera values
        glm::vec2 cameraCenter = Camera::position; // TODO: later position can be actual center, and can alter here
        float scale = viewportScale / Camera::scale;  // TODO: assertion that Camera::scale is not 0??

        for(auto entity : entities)
        {
            TransformComponent& transform = entity.GetComponent<TransformComponent>();
            const auto sprite = entity.GetComponent<SpriteComponent>();
            glm::vec2 textureSize = assetManager->GetTextureSize(sprite.filepath);

            float cos = glm::cos(transform.rotation / 180 * 3.14);
            float sin = glm::sin(transform.rotation / 180 * 3.14);

            SDL_Rect dstRect = {
                static_cast<int>((transform.position.x  - cameraCenter.x) * scale), 
                static_cast<int>(-(transform.position.y - cameraCenter.y) * scale), // Negative so position y-axis points "up"
                static_cast<int>(textureSize.x * glm::abs(transform.scale.x) * scale),
                static_cast<int>(textureSize.y * glm::abs(transform.scale.y) * scale)
            };

            // Handle negative scales by flipping sprite
            SDL_RendererFlip flip = SDL_FLIP_NONE;
            if(transform.scale.x < 0 || transform.scale.y < 0)
            {
                if(transform.scale.x >= 0) flip = SDL_FLIP_VERTICAL;
                else if(transform.scale.y >= 0) flip = SDL_FLIP_HORIZONTAL;
                else flip = static_cast<SDL_RendererFlip>(SDL_FLIP_VERTICAL | SDL_FLIP_HORIZONTAL); 
            }
            

            SDL_RenderCopyEx(
                renderer,
                assetManager->GetTexture(sprite.filepath),
                NULL, &dstRect, -transform.rotation, // rotations are counterclockwise
                NULL, flip
            );
        }
    }
};

#endif // RENDERSYSTEM_H
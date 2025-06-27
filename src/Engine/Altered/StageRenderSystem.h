#ifndef STAGERENDERSYSTEM_H
#define STAGERENDERSYSTEM_H

#include <algorithm>
#include <iostream>

#include <SDL.h>

#include "Engine/Altered/EngineAssetManager.h"

#include "Game/ECS/ECS.h"
#include "Game/Components/TransformComponent.h"
#include "Engine/Altered/EngineSpriteComponent.h"
#include "Engine/Altered/EngineTextComponent.h"


class StageRenderSystem : public System {
public:
    StageRenderSystem() {};

    bool CheckEntity(Entity entity) override
    {
        return entity.HasComponent<EngineSpriteComponent>() || entity.HasComponent<EngineTextComponent>();
    }

    // TODO: dont like this as a unique_ptr reference, or rather unsure if that is optimal?
    void Update(SDL_Renderer* renderer, std::shared_ptr<EngineAssetManager> assetManager, glm::vec2 stageCenter, float stageZoom)
    {
        // TODO: optimize by sorting sprite objects whenever they are added
        // Can do this with a simple insertion on frames with low entity additions
        // And with quicksort (or similar) for ones with more
        std::vector<Entity> entities = GetSystemEntities();
        // TODO: im worried that if objects have same layer, they will swap whos in front
        // Could add a secondary sort value by entityId, higher is above
        std::sort(entities.begin(), entities.end(), [](const Entity& a, const Entity& b)
            { return a.GetComponent<TransformComponent>().zindex
            < b.GetComponent<TransformComponent>().zindex; });

        for(auto entity : entities)
        {
            TransformComponent& transform = entity.GetComponent<TransformComponent>();
            float cos = glm::cos(transform.rotation / 180 * 3.14);
            float sin = glm::sin(transform.rotation / 180 * 3.14);

            if(entity.HasComponent<EngineSpriteComponent>()){
                const auto sprite = entity.GetComponent<EngineSpriteComponent>();
                TextureData textureData = assetManager->GetTexture(sprite.filepath);
                glm::vec2 textureSize = textureData.textureSize;

                SDL_Rect dstRect = {
                    static_cast<int>((transform.position.x  - stageCenter.x) * stageZoom), 
                    static_cast<int>(-(transform.position.y - stageCenter.y) * stageZoom), // Negative so position y-axis points "up"
                    static_cast<int>(textureSize.x * glm::abs(transform.scale.x) * stageZoom),
                    static_cast<int>(textureSize.y * glm::abs(transform.scale.y) * stageZoom)
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
                    textureData.texture,
                    NULL, &dstRect, -transform.rotation, // rotations are counterclockwise
                    NULL, flip
                );
            }
            
            if(entity.HasComponent<EngineTextComponent>()){
                const auto text = entity.GetComponent<EngineTextComponent>();
                glm::vec2 textureSize = assetManager->GetFontTextureSize(text.filepath, text.fontSize, text.text, text.color);

                SDL_Rect dstRect = {
                    static_cast<int>((transform.position.x  - stageCenter.x) * stageZoom), 
                    static_cast<int>(-(transform.position.y - stageCenter.y) * stageZoom), // Negative so position y-axis points "up"
                    static_cast<int>(textureSize.x * glm::abs(transform.scale.x) * stageZoom),
                    static_cast<int>(textureSize.y * glm::abs(transform.scale.y) * stageZoom)
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
                    assetManager->GetFontTexture(text.filepath, text.fontSize, text.text, text.color),
                    NULL, &dstRect, -transform.rotation, // rotations are counterclockwise
                    NULL, flip
                );
            }
        }
    }
};

#endif // STAGERENDERSYSTEM_H
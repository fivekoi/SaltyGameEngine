#include "Engine/History/Edit.h"

#include <fstream>
#include <iostream>
#include <string>
#include <variant>

#include <glm.hpp>
#include <json.hpp>
using json = nlohmann::json;

#include "Game/ECS/ECS.h"
#include "Game/Components/TransformComponent.h"
#include "Engine/Altered/EngineSpriteComponent.h"
#include "Engine/Altered/EngineTextComponent.h"
#include "Game/Components/RigidbodyComponent.h"


/* -----HAS COMPONENT EDIT--------------------- *
 *   When the user adds or removes a component  *
 * -------------------------------------------- */
// Pre: !addComp <-> entity.HasComponent<compType> && |values| = 0 or |compType.args| && compType != TransformComponent
void HasComponentEdit::Apply(bool undo){
    Entity entity = *registry->entityTree[entityId].get(); // TODO: not sure why i deference here, couldnt i just use pointer???
    // add = true -> undo() does RemoveComponent, so addComp = undo xor add (see truth table below)
    /* add      : 0 0 1 1 *
     * undo     : 0 1 0 1 
     * intended : 0 1 1 0 */
    bool addComp = undo != add;

    switch(compType) {
        case SPRITE:
            if(addComp) {
                if(values.empty()) entity.AddComponent<EngineSpriteComponent>(); // default values
                else entity.AddComponent<EngineSpriteComponent>(std::get<std::string>(values[0]));
            }
            else entity.RemoveComponent<EngineSpriteComponent>();
            break;
        case TEXT:
            if(addComp){
                if(values.empty()) entity.AddComponent<EngineTextComponent>(); // default values
                else entity.AddComponent<EngineTextComponent>(std::get<std::string>(values[0]), std::get<std::string>(values[1]), 
                                                              std::get<int>(values[2]), std::get<SDL_Color>(values[3]));
            }
            else entity.RemoveComponent<EngineTextComponent>();
        case RIGIDBODY:
            if(addComp) {
                if(values.empty()) entity.AddComponent<RigidbodyComponent>(); // default values
                else entity.AddComponent<RigidbodyComponent>(glm::vec2(std::get<float>(values[0]), std::get<float>(values[1])));
            }
            else entity.RemoveComponent<RigidbodyComponent>();
            break;
        // case BOXCOL:
        //     // TODO:
        //     break;
        default:
            // TODO: log unidentified component type
            break;
    }

    ApplyJson(undo);
}
// Pre: !addComp <-> entity["components"].contains(compType) && compType != TransformComponent
void HasComponentEdit::ApplyJson(bool undo){
    std::ifstream g("EngineData/current-scene.json");
    json jScene = json::parse(g);
    json jComponents = jScene["entities"][entityId]["components"];

    // add = true -> undo() does RemoveComponent, so addComp = undo xor add (see truth table in Apply())
    bool addComp = undo != add;

    switch(compType) {
        case SPRITE:
            if(addComp) {
                if(values.empty()) { // default values
                    json jSprite = {
                        {"filepath", ""}
                    };
                    jComponents["sprite"] = jSprite;
                }
                else {
                    json jSprite = {
                        {"filepath", std::get<std::string>(values[0])},
                    };
                    jComponents["sprite"] = jSprite;
                }
            }
            else jComponents.erase("sprite");
            break;
        case TEXT:
            if(addComp) {
                if(values.empty()) { // default values
                    json jText = {
                        {"filepath", ""},
                        {"text", ""},
                        {"fontSize", 8},
                        {"color", {0, 0, 0, 255}}
                    };
                    jComponents["text"] = jText;
                }
                else {
                    SDL_Color color = std::get<SDL_Color>(values[3]);
                    json jText = {
                        {"filepath", std::get<std::string>(values[0])},
                        {"text", std::get<std::string>(values[1])},
                        {"fontSize", std::get<int>(values[2])},
                        {"color", {color.r, color.g, color.b, color.a}}
                    };
                    jComponents["text"] = jText;
                }
            }
            else jComponents.erase("text");
            break;
        case RIGIDBODY: 
            if(addComp) {
                if(values.empty()) { // default values
                    json jRigidbody = {
                        {"initVelocity", {0.0, 0.0}}
                    };
                    jComponents["rigidbody"] = jRigidbody;
                }
                else {
                    json jRigidbody = {
                        {"initVelocity", {std::get<float>(values[0]), std::get<float>(values[1])}}
                    };
                    jComponents["rigidbody"] = jRigidbody;
                }
            }
            else jComponents.erase("rigidbody");
            break;
        // case BOXCOL:
        //     // TODO:
        //     break;
        default:
            // TODO: log unidentified component type
            break;
    }
    jScene["entities"][entityId]["components"] = jComponents;
    std::ofstream("EngineData/current-scene.json") << std::setw(2) << jScene;
    g.close();
}

// TODO: dont think this should ever be false? not sure though
bool HasComponentEdit::ValidEdit(){
    return true;
}

std::string HasComponentEdit::ToString(bool undo){    
    std::string componentName = "UNDEFINED COMPONENT";
    switch(compType) {
        case SPRITE:
            componentName = "Sprite";
            break;
        case TEXT:
            componentName = "Text";
            break;
        case RIGIDBODY:
            componentName = "Rigidbody";
            break;
        // case BOXCOL:
        //     // TODO:
        //     break;
    }

    // addComp <-> undo != add (see truth table in Apply())
    std::string action = undo != add ? "Added " + componentName + " to " : "Removed " + componentName + " from ";

    std::string entityName = registry->entityTree[entityId]->name;

    return action + entityName; // TODO: could include entity id here too
}
#include "Engine/History/Edit.h"

#include <algorithm>
#include <fstream>
#include <iostream>
#include <variant>

#include <glm.hpp>
#include <json.hpp>
using json = nlohmann::json;

#include "Game/ECS/ECS.h"


/* -----HAS SCRIPT EDIT------------------------------------- *
 *   When the user adds or removes a script from an entity   *
 * --------------------------------------------------------- */
void HasScriptEdit::Apply(bool undo){
    // add = true -> undo() does RemoveScript, so addScript = undo xor add (see truth table below)
    /* add      : 0 0 1 1 *
     * undo     : 0 1 0 1 
     * intended : 0 1 1 0 */
    bool addScript = undo != add;
    if(addScript){ // Pre: engineData->scriptTree[entityId] not contains scriptData
        engineData->scriptTree[entityId].push_back(scriptData);
        engineData->scriptMap[scriptData.filepath].push_back(entityId);
    }
    else{ // Pre: engineData->scriptTree[entityId] contains scriptData
        int i = 0;
        while(i < engineData->scriptTree[entityId].size() && engineData->scriptTree[entityId][i].filepath != scriptData.filepath){
            i++;
        }
        assert(i < engineData->scriptTree[entityId].size()); // By Pre: should never be the case

        engineData->scriptTree[entityId].erase(engineData->scriptTree[entityId].begin() +  i);
        std::vector<int>& scriptEntities = engineData->scriptMap[scriptData.filepath];
        scriptEntities.erase(std::remove(scriptEntities.begin(), scriptEntities.end(), entityId), scriptEntities.end());
    }


    ApplyJson(undo);
}

void HasScriptEdit::ApplyJson(bool undo){
    std::ifstream g("EngineData/current-scene.json");
    json jScene = json::parse(g);
    json jScripts = jScene["entities"][entityId]["scripts"];
    
    bool addScript = undo != add;
    if(addScript){ // Pre: addScript -> entity["scripts"] not contains scriptData.filepath
        jScripts[scriptData.filepath] = json::array();
        for(int varIdx = 0; varIdx < scriptData.varValues.size(); ++varIdx){
            std::string type = scriptData.varTypes[varIdx];
            if(type == "int"){ // TODO: not a big fan of this big if else stuff, find a workaround, either a switch case, or a mapping to another function on a dict
                jScripts[scriptData.filepath].push_back(std::get<int>(scriptData.varValues[varIdx]));
            }
            else if(type == "float"){
                jScripts[scriptData.filepath].push_back(std::get<float>(scriptData.varValues[varIdx]));
            }
            else if(type == "string"){
                jScripts[scriptData.filepath].push_back(std::get<std::string>(scriptData.varValues[varIdx]));
            }
            else if(type == "Entity*" || type == "Transform*" || type == "Sprite*" || type == "Text*" || type == "Rigidbody*"){
                jScripts[scriptData.filepath].push_back(std::get<int>(scriptData.varValues[varIdx]));
            }
            else if(type == "Sound"){
                Sound sound = std::get<Sound>(scriptData.varValues[varIdx]);
                json jSound = {};
                jSound["filepath"] = sound.filepath;
                jSound["stream"] = sound.stream;
                jScripts[scriptData.filepath].push_back(jSound);
            }
            else {
                // TODO: should be an error instead and have better messaging
                Debug::Log("Unrecognized type");
            }
        }
    }
    else{  // Pre: !addScript -> entity["scripts"] contains scriptData.filepath
        jScripts.erase(scriptData.filepath);
    }

    jScene["entities"][entityId]["scripts"] = jScripts;
    std::ofstream("EngineData/current-scene.json") << std::setw(2) << jScene;
    g.close();
}

// TODO: dont think this should ever be false? not sure though
bool HasScriptEdit::ValidEdit(){
    return true;
}

std::string HasScriptEdit::ToString(bool undo){
    return "Has script edit";
}
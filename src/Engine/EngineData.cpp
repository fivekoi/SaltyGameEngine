#include "Engine/EngineData.h"

#include <fstream>
#include <string>

#include <json.hpp>
using json = nlohmann::json;

EngineData::EngineData(){
    // Open most recently edited project
    std::ifstream f("EngineData/engine-settings.json");
    json jSettings = json::parse(f);
    f.close();

    projectName = jSettings["recent-project"].get<std::string>();
    assetsRootDir = "./Projects/" + projectName + "/Unique/Assets";
    // 1000 / fps = ms per frame
    targetFrameTime = 1000 / jSettings["target-fps"].get<int>();

    // Get engine data specific to recent project
    std::ifstream g("Projects/" + projectName + "/engine.json");
    json jEngineData = json::parse(g);
    g.close();

    // Get engine data specific to project (that is also needed in game build)
    std::ifstream g2("Projects/" + projectName + "/Unique/settings.json");
    json jGameSettings = json::parse(g2);
    json jWindowDimensions = jGameSettings["dimensions"];
    windowDimensions = glm::ivec2(jWindowDimensions[0], jWindowDimensions[1]);
    g2.close();


    // Get all scenes
    std::ifstream h("Projects/" + projectName + "/Unique/scenes.json");
    json jScenes = json::parse(h).begin().value();
    h.close();
    for(int i = 0; i < jScenes.size(); ++i){
        scenes.push_back(jScenes[i].value("name", ""));
    }
    
    // Get most recently open scene
    sceneIndex = jEngineData["recent-scene"].get<int>();
    sceneName = scenes[sceneIndex];
}
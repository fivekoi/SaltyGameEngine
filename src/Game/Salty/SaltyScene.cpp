#include "Game/Salty/SaltyScene.h"

// Will be sent to a val > -1 if a scene needs to be loaded (acts as a flag for Game)
int Scene::sceneToLoad = -1;

void Scene::Load(int sceneIdx){
    sceneToLoad = sceneIdx;
}

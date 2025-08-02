#include "Disrupt.h"

// Called before the first frame of Update()
void Disrupt::Start(){
    if(key == "4"){
        keyCode = KEY_4;
        keyScene = 3;
    }
    else if(key == "C"){
        keyCode = KEY_C;
        keyScene = 5;
    }
    else if(key == "F"){
        keyCode = KEY_F;
        keyScene = 2;
    }
    else if(key == "K"){
        keyCode = KEY_K;
        keyScene = 7;
    }
    else if(key == "M"){
        keyCode = KEY_M;
        keyScene = 4;
    }
    else if(key == "O"){
        keyCode = KEY_O;
        keyScene = 8;
    }
    else if(key == "T"){
        keyCode = KEY_T;
        keyScene = 6;
    }
}

// Called every frame before Render()
void Disrupt::Update(float dt){
    if(phase == 1){
        timer -= dt;
        if(timer <= 0){
            transform->position = where;
            phase = 2;
        }
    }
    else if(phase == 2){
        if(Input::KeyDown[keyCode]){
            if(Scene::sceneToLoad == -1){
                phase = 0;
                mainMini->GetScript<MainMini>()->FinishedDisruption(entity->GetId(), fId);
                Scene::Load(keyScene);
            }
        }
    }
    
}

void Disrupt::Appear(float x, float y, int forwardId, bool wait){
    phase = 1;
    timer = wait ? 2.5 : 0;
    where = {x, y};
    fId = forwardId;
}
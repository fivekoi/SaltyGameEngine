#include "TitleScreen.h"

// Called before the first frame of Update()
void TitleScreen::Start(){

}

// Called every frame before Render()
void TitleScreen::Update(float dt){
    if(Input::KeyDown[KEY_F]){
        Scene::Load(2);
    }
    else if(Input::KeyDown[KEY_4]){
        Scene::Load(3);
    }
    else if(Input::KeyDown[KEY_1]){
        Scene::Load(1);
    }
    else if(Input::KeyDown[KEY_M]){
        Scene::Load(4);
    }
    else if(Input::KeyDown[KEY_C]){
        Scene::Load(5);
    }
    else if(Input::KeyDown[KEY_T]){
        Scene::Load(6);
    }
    else if(Input::KeyDown[KEY_K]){
        Scene::Load(7);
    }
    else if(Input::KeyDown[KEY_O]){
        Scene::Load(8);
    }
}
#include "TitleScreen.h"

// Called before the first frame of Update()
void TitleScreen::Start(){

}

// Called every frame before Render()
void TitleScreen::Update(float dt){
    if(Input::KeyDown[KEY_F]){
        Scene::Load(2);
    }
}
#include "TitleScreen.h"

#include "../Lose/Score.h"

// Called before the first frame of Update()
void TitleScreen::Start(){
    scoreTxt->text = "Highscore: " + std::to_string(Score::highScore);
}

// Called every frame before Render()
void TitleScreen::Update(float dt){
    if(Input::KeyDown[KEY_SPACE]){
        Scene::Load(1);
    }
    else if(Input::KeyDown[KEY_H]){
        Scene::Load(10);
    }
}
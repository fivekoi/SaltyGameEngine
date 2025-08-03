#include "LoseControl.h"

#include "Score.h"

// Called before the first frame of Update()
void LoseControl::Start(){
    if(!score->GetScript<Score>()->wasHighScore){
        highScoreTransform->position.x = 2000;
    }
    scoreText->text = "Score: " + std::to_string(score->GetScript<Score>()->recentScore);
}

// Called every frame before Render()
void LoseControl::Update(float dt){
    if(Input::KeyDown[KEY_T]){
        // TODO: need to reset variables
        Scene::Load(0);
    }
}
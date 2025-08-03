#include "LoseControl.h"

#include "Score.h"
#include "../MainGame/MainMini.h"
#include "../Attention/AttentionBar.h"

// Called before the first frame of Update()
void LoseControl::Start(){
    if(!score->GetScript<Score>()->wasHighScore){
        highScoreTransform->position.x = 2000;
    }
    scoreText->text = "Score: " + std::to_string(score->GetScript<Score>()->recentScore);
    score->GetScript<Score>()->recentScore = 0;
}

// Called every frame before Render()
void LoseControl::Update(float dt){
    if(Input::KeyDown[KEY_T]){
        // Reset all variables
        MainMini::ResetValues();
        AttentionBar::ResetValues();

        Scene::Load(0);
    }
}
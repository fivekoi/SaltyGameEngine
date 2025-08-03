#include "AttentionBar.h"

// Called before the first frame of Update()
void AttentionBar::Start(){
    scoreTxt->text = "Score: " + std::to_string(score);
}

// Called every frame before Render()
void AttentionBar::Update(float dt){
    // Max y = -106
    // Min y = -516
    // 0 y = -522
    float scale = numberOfSolves / 10.0;
    if(scale < 1){
        scale = 1;
    }
    if(scale > 3.5){
        scale = 3.5;
    }
    if(scale > 1 && inMini == 0){
        scale = 1;
    }

    hype -= 1.5 * scale * numberOfDistrupters * dt;

    if(hype < -10){
        transform->position.y = -522;
        Scene::Load(9);
    }
    else{
        float bounded = hype;
        if(hype > 100){
            bounded = 100;
        }
        if(hype < 0){
            bounded = 0;
        }
        float f = bounded / 100.0;

        transform->position.y = (1 - f) * -516 + f * -106;
    }
}

int AttentionBar::DDRInput(bool correct){
    if(correct){
        if(hype < 120){
            hype += 4;
        }
        score += numberOfSolves + 1;
        scoreTxt->text = "Score: " + std::to_string(score);
    }
    else{
        hype -= 12;
    }

    return score;
}

void AttentionBar::ResetValues(){
    score = 0;
    numberOfDistrupters = 0;
    numberOfSolves = 0;
    hype = 50;
}

int AttentionBar::score = 0;
int AttentionBar::numberOfDistrupters = 0;
int AttentionBar::numberOfSolves = 0;
float AttentionBar::hype = 50;
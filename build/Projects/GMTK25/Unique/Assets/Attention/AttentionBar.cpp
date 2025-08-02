#include "AttentionBar.h"

// Called before the first frame of Update()
void AttentionBar::Start(){

}

// Called every frame before Render()
void AttentionBar::Update(float dt){
    // Max y = -106
    // Min y = -516
    // 0 y = -522

    if(transform->position.y > -516){
        transform->position.y -= 50 * dt;
    }
    if(transform->position.y < -106 && Input::KeyDown[KEY_W]){
        transform->position.y += 20;
    }

    

}

void AttentionBar::DDRInput(bool correct){
    if(correct){
        transform->position.y += 30;
    }
    else{
        transform->position.y -= 20;
    }
}
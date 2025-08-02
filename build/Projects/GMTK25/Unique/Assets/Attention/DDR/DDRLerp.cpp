#include "DDRLerp.h"

// Called before the first frame of Update()
void DDRLerp::Start(){

}

// Called every frame before Render()
void DDRLerp::Update(float dt){
    if(lerping){
        timer += 5 * dt;
        transform->position.x = (1 - timer) * start + timer * target;
        if(timer >= 1){
            lerping = false;
            transform->position.x = target;
        }
    }
}

void DDRLerp::LerpTo(float x){
    if(lerping){
        transform->position.x = target;
    }

    timer = 0;
    lerping = true;
    start = transform->position.x;
    target = x;
}

void DDRLerp::CancelLerp(){
    timer = 0;
    lerping = false;
}
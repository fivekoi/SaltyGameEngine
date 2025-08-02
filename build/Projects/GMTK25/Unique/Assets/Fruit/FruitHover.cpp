#include "FruitHover.h"

// Called before the first frame of Update()
void FruitHover::Start(){
    centerY =transform->position.y;
}

// Called every frame before Render()
void FruitHover::Update(float dt){
    timer += dt / 2;
    if(timer >= 1){
        timer = 0;
        up = !up;
    }

    if(up){
        transform->position.y = (1 - timer) * (centerY - 5) + timer * (centerY + 5);
    }
    else{
        transform->position.y = timer * (centerY - 5) + (1 - timer) * (centerY + 5);
    }
}
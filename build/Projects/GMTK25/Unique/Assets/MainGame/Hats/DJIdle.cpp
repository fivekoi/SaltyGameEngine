#include "DJIdle.h"

// Called before the first frame of Update()
void DJIdle::Start(){
    idles.push_back(idle1);
    idles.push_back(idle2);
    idles.push_back(idle3);
    idles.push_back(idle4);
}

// Called every frame before Render()
void DJIdle::Update(float dt){
    timer -= dt;
    if(timer <= 0){
        timer = 0.3;
        i = (i+1) % 4;
        sprite->filepath = idles[i];
    }

}
#include "ColorSwitch.h"

#include "../MainMini.h"

// Called before the first frame of Update()
void ColorSwitch::Start(){
    int diff = mini->GetScript<MainMini>()->difficulty;
    if(diff == 0){
        color1 = green1;
        color2 = green2;
    }
    else if(diff == 1){
        color1 = orange1;
        color2 = orange2;
    }
    else{
        color1 = red1;
        color2 = red2;
    }
}

// Called every frame before Render()
void ColorSwitch::Update(float dt){
    changeTimer -= dt;
    if(changeTimer <= 0){
        changeTimer = 2;
        if(toggle){
            sprite->filepath = green1;
        }
        else{
            sprite->filepath = green2;
        }
        toggle = !toggle;
    }
}
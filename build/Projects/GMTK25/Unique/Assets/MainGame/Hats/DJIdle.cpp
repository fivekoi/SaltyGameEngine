#include "DJIdle.h"

#include "../../Lose/Score.h"

// Called before the first frame of Update()
void DJIdle::Start(){
    idles.push_back(idle1);
    idles.push_back(idle2);
    idles.push_back(idle3);
    idles.push_back(idle4);

    if(hat == 1 && Score::highScore >= 3500){
        idles.clear();
        idles.push_back("MainGame/Hats/Crown/crown1.png");
        idles.push_back("MainGame/Hats/Crown/crown2.png");
        idles.push_back("MainGame/Hats/Crown/crown3.png");
        idles.push_back("MainGame/Hats/Crown/crown4.png");
    }
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
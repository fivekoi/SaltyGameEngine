#include "CrownRemove.h"

#include "../../../Lose/Score.h"

// Called before the first frame of Update()
void CrownRemove::Start(){
    if(Score::highScore >= 3500){
        transform->position.x += 2000;
        text1->position.y += 1000;
        text2->position.y += 1000;
    }
}

// Called every frame before Render()
void CrownRemove::Update(float dt){

}
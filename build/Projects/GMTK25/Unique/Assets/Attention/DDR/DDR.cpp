#include "DDR.h"

#include "DDRLerp.h"
#include "../AttentionBar.h"
#include "../../Lose/Score.h"

#include <cstdlib>
#include <ctime>

// Called before the first frame of Update()
void DDR::Start(){
    availKeys.push_back(w1);
    availKeys.push_back(w2);
    availKeys.push_back(w3);
    availKeys.push_back(w4);
    availKeys.push_back(a1);
    availKeys.push_back(a2);
    availKeys.push_back(a3);
    availKeys.push_back(a4);
    availKeys.push_back(d1);
    availKeys.push_back(d2);
    availKeys.push_back(d3);
    availKeys.push_back(d4);

    srand(time(0));
    
    int r = rand() % availKeys.size();
    availKeys[r]->GetComponent<TransformComponent>().position.x = 220;
    usedKeys.push_back(availKeys[r]);
    usedInputs.push_back(availInputs[r]);
    availKeys.erase(availKeys.begin() + r);
    availInputs.erase(availInputs.begin() + r);

    for(int i = 1; i < 8; ++i){
        r = rand() % availKeys.size();
        availKeys[r]->GetComponent<TransformComponent>().position.x = 300 + 80 * (i - 1);

        usedKeys.push_back(availKeys[r]);
        usedInputs.push_back(availInputs[r]);
        availKeys.erase(availKeys.begin() + r);
        availInputs.erase(availInputs.begin() + r);
    }

    for(size_t i = 0; i < availKeys.size(); ++i){
        availKeys[i]->GetComponent<TransformComponent>().position.x = 1000;
    }
}

// Called every frame before Render()
void DDR::Update(float dt){
    if(Input::KeyDown[usedInputs[0]]){
        usedKeys[0]->GetScript<DDRLerp>()->CancelLerp();
        usedKeys[0]->GetComponent<TransformComponent>().position.x = 1000;
        Entity* e = usedKeys[0];
        int input = usedInputs[0];
        usedKeys.erase(usedKeys.begin());
        usedInputs.erase(usedInputs.begin());

        int r = rand() % availKeys.size();
        usedKeys.push_back(availKeys[r]);
        usedInputs.push_back(availInputs[r]);
        availKeys.erase(availKeys.begin() + r);
        availInputs.erase(availInputs.begin() + r);

        for(int i = 0; i < 8; ++i){
            usedKeys[i]->GetScript<DDRLerp>()->LerpTo(220 + 80 * i);
        }

        availKeys.push_back(usedKeys[0]);
        availInputs.push_back(usedInputs[0]);

        int s = attention->GetScript<AttentionBar>()->DDRInput(true);
        score->GetScript<Score>()->recentScore = s;
    } // This elses will only happen if the first if isnt satisfied (so will be wrong input)
    else if(Input::KeyDown[KEY_W] || Input::KeyDown[KEY_A] || Input::KeyDown[KEY_D]){
        attention->GetScript<AttentionBar>()->DDRInput(false);
    }
}
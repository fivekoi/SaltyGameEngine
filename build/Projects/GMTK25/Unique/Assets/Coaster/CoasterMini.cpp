#include "CoasterMini.h"

// Called before the first frame of Update()
void CoasterMini::Start(){
    coaster->position = positions[0];
    coaster->rotation = rotations[0];

    for(size_t i = 0; i < rotations.size()-1; ++i){
        if(i != 1 && i != 9 && rotations[i] != rotations[i+1]){
            glm::vec2 mid = 0.5f * (positions[i] + positions[i+1]);
            glm::vec2 dir = positions[i+1] - positions[i];
            glm::vec2 perp = glm::normalize(glm::vec2(-dir.y, dir.x));

            float arcHeight = -50;
            if(i == 8){
                arcHeight = -70;
            }
            centerPoints.push_back(mid + arcHeight * perp);
        }
        else{
            centerPoints.push_back({0, 0});
        }
    }
}

// Called every frame before Render()
void CoasterMini::Update(float dt){
    if(!won){
        timer += dt;
        if(timer >= times[idx]){
            timer = 0;
            idx = (idx + 1) % (times.size() - 1);
            if(idx == 0){
                timer = -2;
            }
        }
        else{
            float percent = timer / times[idx];
            if(centerPoints[idx] == glm::vec2{0, 0}){
                coaster->position = (1 - percent) * positions[idx] + percent * positions[idx + 1];
                
            }
            else{
                coaster->position = (1 - percent) * (1 - percent) * positions[idx] 
                                    + 2 * (1 - percent) * percent * centerPoints[idx]
                                    + percent * percent * positions[idx + 1];
            }
            coaster->rotation = (1 - percent) * rotations[idx] + percent * rotations[idx + 1];
        }

        if(Input::KeyDown[KEY_SPACE]){
            if(674 <= coaster->position.x && coaster->position.x <= 925){
                std::cout << "won\n";
                won = true;
            }
        }
    }

    // Final timer just to animate ding
    if(won){
        check->position.x = 216;
        check->position.y = -53;
        winTimer -= dt;
        if(winTimer <= 0){
            Scene::Load(1);
        }
    }
}
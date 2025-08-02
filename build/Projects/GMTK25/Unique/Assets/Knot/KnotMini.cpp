#include "KnotMini.h"

#include <cstdlib>
#include <ctime>


// Called before the first frame of Update()
void KnotMini::Start(){
    srand(time(0));

    left = rand() % leftKeys.size();
    leftLetterText->text = leftKeyLetters[left];

    right = rand() % rightKeys.size();
    rightLetterText->text = rightKeyLetters[right];
}

// Called every frame before Render()
void KnotMini::Update(float dt){
    if(!won){
        if(leftPresses < 10 && Input::KeyDown[leftKeys[left]]){
            leftPresses += 1;
            leftLetterTransform->position.x -= 10;

            knotTransform->position.x -= 10;

            if(leftPresses >= 10 && rightPresses >= 10){
                std::cout << "won\n";
                knotSprite->filepath = knot3;
                won = true;
            }
            else if(leftPresses + rightPresses >= 10){
                knotSprite->filepath = knot2;
            }
        }
        if(rightPresses < 10 && Input::KeyDown[rightKeys[right]]){
            rightPresses += 1;
            rightLetterTransform->position.x += 10;

            knotTransform->position.x += 10;

            if(leftPresses >= 10 && rightPresses >= 10){
                std::cout << "won\n";
                knotSprite->filepath = knot3;
                won = true;
            }
            else if(leftPresses + rightPresses >= 10){
                knotSprite->filepath = knot2;
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
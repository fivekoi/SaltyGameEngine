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

            if(leftPresses >= 10 && rightPresses >= 10){
                std::cout << "won\n";
                won = true;
            }
        }
        if(rightPresses < 10 && Input::KeyDown[rightKeys[right]]){
            rightPresses += 1;
            rightLetterTransform->position.x += 10;

            if(leftPresses >= 10 && rightPresses >= 10){
                std::cout << "won\n";
                won = true;
            }
        }
    }
}
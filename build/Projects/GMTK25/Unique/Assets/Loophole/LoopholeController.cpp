#include "LoopholeController.h"

#include <cstdlib>
#include <ctime>

// Called before the first frame of Update()
void LoopholeController::Start(){
    srand(time(0));
}

// Called every frame before Render()
void LoopholeController::Update(float dt){
    if(!won){        
        if(Input::KeyDown[KEY_SPACE]){
            if(statementIndex = falseIndex){
                std::cout << "won\n";
                won = true;
            }
        }

        timer -= dt;
        if(timer <= 0){
            timer = 2;
            statementIndex = (statementIndex + 1) % 3;
            textTransform->position.y = -350 + (rand() % 200);

            if(statementIndex == 0){
                // Generates which of the next 3 will be false
                falseIndex = rand() % 3;
                nextThree.clear();
                int pushedTrue = -1;
                for(int i = 0; i < 3; i++){
                    if(falseIndex == i){
                        int falseIdx = rand() % lies.size();
                        nextThree.push_back(lies[falseIdx]);
                    }
                    else if(pushedTrue == -1){
                        pushedTrue = rand() % truths.size();
                        nextThree.push_back(truths[pushedTrue]);
                    }
                    else{
                        pushedTrue += (rand() % (truths.size() - 1));
                        pushedTrue = pushedTrue % truths.size();
                        nextThree.push_back(truths[pushedTrue]);
                    }
                }

                mainText->text = nextThree[statementIndex];
            }
            else{
                mainText->text = nextThree[statementIndex];
            }
        }

        
    }
    
}
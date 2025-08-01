#include "LoopholeController.h"

#include <cstdlib>
#include <ctime>

// Called before the first frame of Update()
void LoopholeController::Start(){
    srand(time(0));

    timer = 2;
    statementIndex = 0;
    textTransform->position.y = -350 + (rand() % 200);

    GenerateStatements();
    mainText->text = nextThree[statementIndex];
}

void LoopholeController::GenerateStatements(){
    // Generates which of the next 3 will be false
    falseIndex = rand() % 3;
    nextThree.clear();
    for(int i = 0; i < 3; ++i){
        if(falseIndex == i){
            nextThree.push_back(lies[rand() % lies.size()]);
        }
        else{
            pushedTrue += 1 + rand() % (truths.size() - 2);
            pushedTrue = pushedTrue % truths.size();
            nextThree.push_back(truths[pushedTrue]);
        }
    }
}

// Called every frame before Render()
void LoopholeController::Update(float dt){
    if(!won){        
        if(Input::KeyDown[KEY_SPACE]){
            if(statementIndex == falseIndex){
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
                GenerateStatements();
            }
            mainText->text = nextThree[statementIndex];

        }

        
    }
    
}
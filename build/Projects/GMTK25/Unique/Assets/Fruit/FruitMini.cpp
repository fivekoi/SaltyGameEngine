#include "FruitMini.h"

#include <cstdlib>
#include <ctime>

// Called before the first frame of Update()
void FruitMini::Start(){
    srand(time(0));
    randomFruit = rand() % 3;

    

    std::cout << randomFruit << '\n';
}

// Called every frame before Render()
void FruitMini::Update(float dt){
    if(!won && Input::KeyDown[fruitsKeys[randomFruit][currentLetter]]){
        std::cout << "correct\n";
        currentLetter += 1;
        if(currentLetter >= fruitsKeys[randomFruit].size()){
            std::cout << "win\n";
            won = true;
        }
    }
}
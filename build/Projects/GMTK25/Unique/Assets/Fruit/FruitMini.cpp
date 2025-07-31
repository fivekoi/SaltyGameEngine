#include "FruitMini.h"

#include <cstdlib>
#include <ctime>

// Called before the first frame of Update()
void FruitMini::Start(){
    srand(time(0));
    randomFruit = rand() % 3;

    std::string blanks = "";
    for(size_t i = 0; i < fruitsKeys[randomFruit].size(); ++i){
        blanks += "_ ";
    }
    inputText->text = blanks;

    // Temp for debug
    debugText->text = fruitStrings[randomFruit];
}

// Called every frame before Render()
void FruitMini::Update(float dt){
    if(!won && Input::KeyDown[fruitsKeys[randomFruit][currentLetter]]){
        std::string str = inputText->text;
        str[2*currentLetter] = fruitStrings[randomFruit][currentLetter];
        inputText->text = str;

        currentLetter += 1;
        if(currentLetter >= fruitsKeys[randomFruit].size()){
            std::cout << "win\n";
            won = true;
        }
    }
}
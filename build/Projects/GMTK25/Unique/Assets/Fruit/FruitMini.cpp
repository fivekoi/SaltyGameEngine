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

    if(randomFruit == 0){
        // banana
        HideChildren(apple);
        HideChildren(orange);
    }
    else if(randomFruit == 1){
        // apple
        HideChildren(banana);
        HideChildren(orange);
    }
    else if(randomFruit == 2){
        // orange
        HideChildren(banana);
        HideChildren(apple);
    }
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

void FruitMini::HideChildren(Entity* e){
    for(int id : e->childrenIds){
        entity->registry->entityTree[id]->GetComponent<TransformComponent>().position.x = 1000;
    }
}
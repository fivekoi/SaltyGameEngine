#include "ForMini.h"

#include <cstdlib>
#include <ctime>

#include "../Sounds/SoundManager.h"

// Called before the first frame of Update()
void ForMini::Start(){
    srand(time(0));

    int start = rand() % 3;
    int end = 7 + rand() % 3;
    int inc = 1 + rand() % 2;
    if(inc == 1){
        end -= 2;
    }

    forText->text = "for(int i = " + std::to_string(start) + "; i < " + std::to_string(end) + "; i += " + std::to_string(inc) + "){"; 

    valueString = "";
    for(int i = start; i < end; i += inc){
        values.push_back(i);
        valueString += std::to_string(i);
    }

    std::string blanks = "";
    for(size_t i = 0; i < values.size(); ++i){
        blanks += "_ ";
    }
    inputText->text = blanks;

    Audio::Play(SoundManager::typing);
}

// Called every frame before Render()
void ForMini::Update(float dt){
    if(!won && Input::KeyDown[numberKeys[values[currentNumber]]]){
        std::string str = inputText->text;
        str[2*currentNumber] = valueString[currentNumber];
        inputText->text = str;

        currentNumber += 1;
        if(currentNumber >= values.size()){
            std::cout << "win\n";
            won = true;

            Audio::Play(SoundManager::winding);
            Audio::Stop(SoundManager::typing);
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
#include "MicMini.h"

#include <cstdlib>
#include <ctime>

// Called before the first frame of Update()
void MicMini::Start(){
    srand(time(0));

    int startNum = rand() % numbers.size();
    letter1->text = std::to_string(numbers[startNum]);
    letter2->text = std::to_string(numbers[(startNum + 1) % numbers.size()]);
    letter3->text = std::to_string(numbers[(startNum + 2) % numbers.size()]);
    letter4->text = std::to_string(numbers[(startNum + 3) % numbers.size()]);

    std::vector<string> sprites;
    sprites.push_back(mic1);
    sprites.push_back(mic2);
    sprites.push_back(mic3);
    sprites.push_back(mic4);
    int which = rand() % 4;
    mic->filepath = sprites[which];
    correct = numberKeys[(startNum + which) % numbers.size()];
}

// Called every frame before Render()
void MicMini::Update(float dt){
    if(Input::KeyDown[correct]){
        std::cout << "won\n";
        won = true;
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
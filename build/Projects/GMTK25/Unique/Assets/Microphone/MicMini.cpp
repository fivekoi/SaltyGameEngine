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

    int which = rand() % 4;
    std::cout << which << '\n';
    correct = numberKeys[(startNum + which) % numbers.size()];
}

// Called every frame before Render()
void MicMini::Update(float dt){
    if(Input::KeyDown[correct]){
        std::cout << "won\n";
        won = true;
    }
}
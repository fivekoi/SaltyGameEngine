#include "TextUpdate.h"

#include <cmath>
#include <string>

// Called before the first frame of Update()
void TextUpdate::Start(){
    
}

// Called every frame before Render()
void TextUpdate::Update(float dt){
    timer += dt;
    counter = 10 * std::round(timer);

    // text->fontSize = counter;
    text->text = std::to_string(int(std::round(timer)));
    text->color = {counter, 0, 0, counter};
}
#include "TextUpdate.h"
#include "PlayerMovement.h"

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

    if(Input::KeyDown[KEY_2]){
        if(Scene::currentScene == 0){
            Scene::Load(1);
        }
        else{
            Scene::Load(0);
        }
    }
    
    if(Input::KeyDown[KEY_3]){
        other->GetScript<PlayerMovement>()->Three();
    }

    if(Input::KeyDown[KEY_I]){
        count += 1;
        std::cout << count << '\n';
    }
}

int TextUpdate::count = 0;
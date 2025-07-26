#include "PlayerMovement.h"

// TODO: NOTE: Decided to seperate header file and .cpp file
// Helps with correctness of c++ code, and may even be quicker to access stuff for jams
// TODO: when you double click on something in engine, open both .h and .cpp
// TODO: also group them inside file directory

// Called before the first frame of Update()
void PlayerMovement::Start(){
    sound.filepath = "boop.wav";
    sound.stream = false;
    Audio::Load(sound);

    Camera::position.x = 1;

    sprite->filepath = sprite2;
}

// TODO: may add more detail
// Called every frame before Render() 
void PlayerMovement::Update(float dt){
    if(Input::KeyHeld[KEY_A]){
        player->position.x -= dt * speed;
    }
    if(Input::KeyHeld[KEY_D]){
        transform->position.x += dt * speed;
    }
    if(Input::KeyUp[KEY_0]){
        std::cout << "0\n";
    }

    if(Input::KeyDown[KEY_S]){
        Audio::Play(sound);
        std::cout << val << '\n';
        val += 3;
    }

    if(Input::KeyHeld[KEY_W]){
        std::cout << Input::MouseX << '\n';
    }

    if(Input::KeyDown[KEY_C]){
        whichSprite = !whichSprite;
        if(whichSprite){
            sprite->filepath = sprite1;
        }
        else{
            sprite->filepath = sprite2;
        }
    }
}
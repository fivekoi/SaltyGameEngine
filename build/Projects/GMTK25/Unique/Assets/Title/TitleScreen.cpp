#include "TitleScreen.h"

#include "../Lose/Score.h"
#include "../Sounds/SoundManager.h"

// Called before the first frame of Update()
void TitleScreen::Start(){
    scoreTxt->text = "Highscore: " + std::to_string(Score::highScore);
}

// Called every frame before Render()
void TitleScreen::Update(float dt){
    if(playMusic){
        Audio::Play(SoundManager::title);
        playMusic = false;
    }

    if(Input::KeyDown[KEY_SPACE]){
        playMusic = true;
        Audio::Stop(SoundManager::title);
        Scene::Load(1);
    }
    else if(Input::KeyDown[KEY_H]){
        Scene::Load(10);
    }
}

bool TitleScreen::playMusic = true;
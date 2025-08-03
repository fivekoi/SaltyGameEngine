#include "SoundManager.h"

// Called before the first frame of Update()
void SoundManager::Start(){
    if(!loaded){
        drum1.filepath = "Sounds/Drum1.wav";
        drum1.stream = false;
        Audio::Load(drum1);

        drum2.filepath = "Sounds/Drum2.wav";
        drum2.stream = false;
        Audio::Load(drum2);

        music.filepath = "Sounds/GameMusic.wav";
        music.stream = true;
        Audio::Load(music);

        cereal.filepath = "Sounds/cereal.wav";
        cereal.stream = false;
        Audio::Load(cereal);

        coaster.filepath = "Sounds/coaster.wav";
        coaster.stream = false;
        Audio::Load(coaster);

        lose.filepath = "Sounds/lose.wav";
        lose.stream = false;
        Audio::Load(lose);

        micfeedback.filepath = "Sounds/micfeedback.wav";
        micfeedback.stream = false;
        Audio::Load(micfeedback);

        rope.filepath = "Sounds/rope.wav";
        rope.stream = false;
        Audio::Load(rope);

        ticktock.filepath = "Sounds/ticktock.wav";
        ticktock.stream = false;
        Audio::Load(ticktock);

        ticktockrev.filepath = "Sounds/ticktockrev.wav";
        ticktockrev.stream = false;
        Audio::Load(ticktockrev);

        typing.filepath = "Sounds/typing.wav";
        typing.stream = false;
        Audio::Load(typing);

        winding.filepath = "Sounds/winding.wav";
        winding.stream = false;
        Audio::Load(winding);

        wrong.filepath = "Sounds/wrong.wav";
        wrong.stream = false;
        Audio::Load(wrong);

        title.filepath = "Sounds/TitleMusic.wav";
        title.stream = false;
        Audio::Load(title);

        loaded = true;
    }
}

// Called every frame before Render()
void SoundManager::Update(float dt){

}

bool SoundManager::loaded = false;
Sound SoundManager::drum1;
Sound SoundManager::drum2;
Sound SoundManager::music;
Sound SoundManager::cereal;
Sound SoundManager::coaster;
Sound SoundManager::lose;
Sound SoundManager::micfeedback;
Sound SoundManager::rope;
Sound SoundManager::ticktock;
Sound SoundManager::ticktockrev;
Sound SoundManager::typing;
Sound SoundManager::winding;
Sound SoundManager::wrong;
Sound SoundManager::title;

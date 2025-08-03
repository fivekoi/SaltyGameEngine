#include "TimeMini.h"

#include "../Sounds/SoundManager.h"

// Called before the first frame of Update()
void TimeMini::Start(){
    walkFrames.push_back(walk1);
    walkFrames.push_back(walk2);
    walkFrames.push_back(walk3);
    walkFrames.push_back(walk4);

    srand(time(0));
    for(int i = 0; i < 3; ++i){
        int j = rand() % letters.size();
        goalIdxs.push_back(j);
    }

    goalText->text = "";

    Audio::Play(SoundManager::ticktock);
}

// Called every frame before Render()
void TimeMini::Update(float dt){
    if(!won){
        if(phase == 0){
            walkTimer -= dt;
            if(walkTimer <= 0){
                walkTimer = 0.2;
                walkIndex = (walkIndex + 1) % walkFrames.size();

                walkSprite->filepath = walkFrames[walkIndex];   
            }
            if(walkTransform->position.x <= 720){
                // 20 -> 720
                walkTransform->position.x += 300 * dt;
            }
            else{
                walkTransform->position.x = 720;
                walkTimer = 0;
                phase = 1;
                Audio::Play(SoundManager::ticktockrev);
            }

            if(walkTransform->position.x >= 90 && textRevealed == 0){
                goalText->text = letters[goalIdxs[textRevealed]] + "       ";
                textRevealed = 1;
            }
            if(walkTransform->position.x >= 368 && textRevealed == 1){
                std::string str = goalText->text;
                str += letters[goalIdxs[textRevealed]] + "       ";
                goalText->text = str;
                textRevealed = 2;
            }
            if(walkTransform->position.x >= 655 && textRevealed == 2){
                std::string str = goalText->text;
                str += letters[goalIdxs[textRevealed]] + "       ";
                goalText->text = str;
                textRevealed = 3;
            }
        }
        else if(phase == 1){
            walkTimer -= dt;
            if(walkTimer <= 0){
                walkTimer = 0.1;
                walkIndex = (walkIndex + 1) % walkFrames.size();

                walkSprite->filepath = walkFrames[walkIndex];   
            }
            if(walkTransform->position.x >= 20){
                // 20 -> 720
                walkTransform->position.x -= 600 * dt;
            }
            else{
                walkTransform->position.x = 20;
                goalText->text = "";
                textRevealed = 0;
                phase = 2;
            }
        }
        else if(phase == 2){
            if(Input::KeyDown[KEY_R]){
                walkTransform->position.x = 20;
                goalText->text = "";
                textRevealed = 0;
                Audio::Play(SoundManager::ticktock);
                phase = 0;
            } 
            else if(Input::KeyDown[letterKeys[goalIdxs[textRevealed]]]){
                walkTransform->position.x = letterPositions[textRevealed];
                walkIndex = (walkIndex + 1) % walkFrames.size();
                walkSprite->filepath = walkFrames[walkIndex];   

                if(textRevealed == 0){
                    goalText->text = letters[goalIdxs[textRevealed]] + "       ";
                }
                if(textRevealed == 1){
                    std::string str = goalText->text;
                    str += letters[goalIdxs[textRevealed]] + "       ";
                    goalText->text = str;
                }
                if(textRevealed == 2){
                    std::string str = goalText->text;
                    str += letters[goalIdxs[textRevealed]] + "       ";
                    goalText->text = str;
                }

                textRevealed += 1;
                if(textRevealed == 3){
                    std::cout << "won\n";
                    won = true;

                    Audio::Play(SoundManager::winding);
                }
            }
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
#include "PersonController.h"

// Called before the first frame of Update()
void PersonController::Start(){
    //MainGame\Idle/Idle1.png
    std::string frame1 = entity->GetComponent<SpriteComponent>().filepath;
    if(frame1 == "MainGame\\Idle/Idle1.png"){
        idleFrames.push_back("MainGame\\Idle/Idle1.png");
        idleFrames.push_back("MainGame\\Idle/Idle2.png");
        idleFrames.push_back("MainGame\\Idle/Idle3.png");
        idleFrames.push_back("MainGame\\Idle/Idle4.png");
    }
    else if(frame1 == "MainGame\\Idle/Idle5.png"){
        idleFrames.push_back("MainGame\\Idle/Idle5.png");
        idleFrames.push_back("MainGame\\Idle/Idle6.png");
        idleFrames.push_back("MainGame\\Idle/Idle7.png");
        idleFrames.push_back("MainGame\\Idle/Idle8.png");
    }
    else if(frame1 == "MainGame\\Idle/Idle9.png"){
        idleFrames.push_back("MainGame\\Idle/Idle9.png");
        idleFrames.push_back("MainGame\\Idle/Idle10.png");
        idleFrames.push_back("MainGame\\Idle/Idle11.png");
        idleFrames.push_back("MainGame\\Idle/Idle12.png");
    }
    else if(frame1 == "MainGame\\Idle/Idle13.png"){
        idleFrames.push_back("MainGame\\Idle/Idle13.png");
        idleFrames.push_back("MainGame\\Idle/Idle14.png");
        idleFrames.push_back("MainGame\\Idle/Idle15.png");
        idleFrames.push_back("MainGame\\Idle/Idle16.png");
    }
}

// Called every frame before Render()
void PersonController::Update(float dt){
    if(walkingOn){
        walkOnTimer += dt;
        if(walkOnTimer < 2){
            transform->position.x = (1 - walkOnTimer / 2) * startX + (walkOnTimer / 2) * goalX;
        }   
        else{
            isIdle = true;
            walkingOn = false;
            walkOnTimer = 0;
            transform->position.x = goalX;
            transform->scale.x = facing;
            entity->GetComponent<SpriteComponent>().filepath = idleFrames[localFrame];
        }
    }

    if(walkingOff){
        walkOnTimer += dt;
        if(walkOnTimer < 2){
            transform->position.x = (1 - walkOnTimer / 2) * goalX + (walkOnTimer / 2) * startX;
        }   
        else{
            isIdle = true;
            walkingOff = false;
            walkOnTimer = 0;
            transform->position.x = startX;
        }
    }
}

void PersonController::Tick(int frame){
    localFrame = frame;
    if(walkingOn || walkingOff){
        entity->GetComponent<SpriteComponent>().filepath = walkFrames[localFrame];
    }   
    else{
        entity->GetComponent<SpriteComponent>().filepath = idleFrames[localFrame];
    }
}

void PersonController::WalkOn(){
    // -x is right
    if(startX < goalX){
        if(transform->scale.x > 0){
            transform->scale.x *= -1;    
        }
    }
    else{
        if(transform->scale.x < 0){
            transform->scale.x *= -1;    
        }
    }
    walkOnTimer = 0;
    isIdle = false;
    walkingOn = true;
}

void PersonController::WalkOff(){
    // -x is right
    if(startX < goalX){
        if(transform->scale.x < 0){
            transform->scale.x *= -1;    
        }
    }
    else{
        if(transform->scale.x > 0){
            transform->scale.x *= -1;    
        }
    }
    walkOnTimer = 0;
    isIdle = false;
    walkingOff = true;
}

bool PersonController::IsIdle(){
    return isIdle;
}
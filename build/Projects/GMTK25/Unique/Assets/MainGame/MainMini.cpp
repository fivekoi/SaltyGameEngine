#include "MainMini.h"

#include "PersonController.h"

// Called before the first frame of Update()
void MainMini::Start(){
    for(int pId : entity->childrenIds){
        for(int id : entity->registry->entityTree[pId]->childrenIds){
            peopleOff.push_back(id);
        }
    }

    for(int id : peopleOff){
        Transform& t = entity->registry->entityTree[id]->GetComponent<TransformComponent>();
        entity->registry->entityTree[id]->GetScript<PersonController>()->goalX = t.position.x;
        if(t.position.x < 397){
            t.position.x = -90;
            entity->registry->entityTree[id]->GetScript<PersonController>()->startX = -90;
        }
        else{
            t.position.x = 970;
            entity->registry->entityTree[id]->GetScript<PersonController>()->startX = 970;
        }

        entity->registry->entityTree[id]->GetScript<PersonController>()->facing = t.scale.x;
    }
}

// Called every frame before Render()
void MainMini::Update(float dt){
    timer -= dt;
    if(timer <= 0){
        timer = 0.3f;
        frameNum = (frameNum + 1) % 4;

        for(int id : peopleOn){
            entity->registry->entityTree[id]->GetScript<PersonController>()->Tick(frameNum);
        }
        for(int id : peopleOff){
            entity->registry->entityTree[id]->GetScript<PersonController>()->Tick(frameNum);
        }
    }

    walkTimer -= dt;
    if(walkTimer <= 0 && peopleOff.size() > 0){
        walkTimer = 3;
        entity->registry->entityTree[peopleOff[0]]->GetScript<PersonController>()->WalkOn();
        peopleOn.push_back(peopleOff[0]);
        peopleOff.erase(peopleOff.begin());

        if(peopleOn.size() >= 3){
            if(entity->registry->entityTree[peopleOn[0]]->GetScript<PersonController>()->IsIdle()){
                entity->registry->entityTree[peopleOn[0]]->GetScript<PersonController>()->WalkOff();
                peopleOff.push_back(peopleOn[0]);
                peopleOn.erase(peopleOn.begin());
            }
        }
    }
}
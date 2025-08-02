#include "MainMini.h"

#include "PersonController.h"

#include <cstdlib>
#include <ctime>

// Called before the first frame of Update()
void MainMini::Start(){
    srand(time(0));

    if(!started){
        // Start summoning people (including 2 facing forwards...)
        started = true;

        for(int pId : entity->childrenIds){
            for(int id : entity->registry->entityTree[pId]->childrenIds){
                std::string fp = entity->registry->entityTree[id]->GetComponent<SpriteComponent>().filepath;
                if(fp == "MainGame\\Idle/Idle1.png"){
                    forwardPeopleOff.push_back(id);
                }
                else{
                    peopleOff.push_back(id);
                }
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
        for(int id : forwardPeopleOff){
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

        int r = rand() % forwardPeopleOff.size();
        entity->registry->entityTree[forwardPeopleOff[r]]->GetScript<PersonController>()->WalkOn();
        forwardPeopleOn.push_back(forwardPeopleOff[r]);
        forwardPeopleOff.erase(forwardPeopleOff.begin() + r);

        for(int i = 0; i < 5; ++i){
            r = rand() % peopleOff.size();

            entity->registry->entityTree[peopleOff[r]]->GetScript<PersonController>()->WalkOn();
            peopleOn.push_back(peopleOff[r]);
            peopleOff.erase(peopleOff.begin() + r);
        }
    }
    else{
        // Restore people to their positions from before
        for(int pId : entity->childrenIds){
            for(int id : entity->registry->entityTree[pId]->childrenIds){
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

        for(int id : peopleOn){
            Transform& t = entity->registry->entityTree[id]->GetComponent<TransformComponent>();
            t.position.x = entity->registry->entityTree[id]->GetScript<PersonController>()->goalX;
        }
        for(int id : forwardPeopleOn){
            Transform& t = entity->registry->entityTree[id]->GetComponent<TransformComponent>();
            t.position.x = entity->registry->entityTree[id]->GetScript<PersonController>()->goalX;
        }
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


    if(Input::KeyDown[KEY_0]){
        Scene::Load(0);
    }
}

bool MainMini::started = false;
std::vector<int> MainMini::peopleOff;
std::vector<int> MainMini::peopleOn;
std::vector<int> MainMini::forwardPeopleOff;
std::vector<int> MainMini::forwardPeopleOn;
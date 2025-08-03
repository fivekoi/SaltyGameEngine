#include "MainMini.h"

#include "PersonController.h"
#include "./KeySymbols/Disrupt.h"
#include "../Attention/AttentionBar.h"
#include "../Sounds/SoundManager.h"

#include <algorithm>
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
                if(fp == "MainGame/Idle/Idle1.png"){
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

        // Add disruptions to vector
        for(auto id : disruptionParent->childrenIds){
            availableDisruptions.push_back(id);
        }

        Audio::Play(SoundManager::music, true);
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
        for(int id : forwardPeopleDisrupt){
            Transform& t = entity->registry->entityTree[id]->GetComponent<TransformComponent>();
            t.position.x = entity->registry->entityTree[id]->GetScript<PersonController>()->goalX;
        }

        for(auto& pair : usedDisruptions){
            Transform& t = entity->registry->entityTree[pair.second]->GetComponent<TransformComponent>();
            float y = t.position.y - 20;
            // if size = 5 -> 8
            // otherwise -> 6
            float offset = 6;
            if(t.scale.x == 5.0){
                offset = 11;
            }
            else if(t.scale.x == 4.0){
                offset = 5.25;
            }
            float x = entity->registry->entityTree[pair.second]->GetScript<PersonController>()->goalX + offset;
            entity->registry->entityTree[pair.first]->GetScript<Disrupt>()->Appear(x, y, pair.second, false);
        }
        // Make disrupter walk off
        entity->registry->entityTree[disrupter]->GetScript<PersonController>()->WalkOff();
        forwardPeopleOff.push_back(disrupter);
        forwardPeopleOn.erase(std::remove(forwardPeopleOn.begin(), forwardPeopleOn.end(), disrupter), forwardPeopleOn.end());

        attentionBar->GetScript<AttentionBar>()->numberOfDistrupters -= 1;

        if(peopleOff.size() >= 5){
            for(int i = 0; i < 5; ++i){
                int r = rand() % peopleOff.size();

                entity->registry->entityTree[peopleOff[r]]->GetScript<PersonController>()->WalkOn();
                peopleOn.push_back(peopleOff[r]);
                peopleOff.erase(peopleOff.begin() + r);
            }
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
        for(int id : forwardPeopleOn){
            entity->registry->entityTree[id]->GetScript<PersonController>()->Tick(frameNum);
        }
        for(int id : forwardPeopleOff){
            entity->registry->entityTree[id]->GetScript<PersonController>()->Tick(frameNum);
        }
        for(int id : forwardPeopleDisrupt){
            entity->registry->entityTree[id]->GetScript<PersonController>()->Tick(frameNum);
        }
    }

    disruptTimer -= dt;
    if(disruptTimer <= 1 && dis){
        dis = false;
        if(peopleOn.size() >= 3){
            int n = rand() % 3 + 1;
            for(int i = 0; i < n; ++i){
                int r = rand() % peopleOn.size();

                entity->registry->entityTree[peopleOn[r]]->GetScript<PersonController>()->WalkOff();
                peopleOff.push_back(peopleOn[r]);
                peopleOn.erase(peopleOn.begin());
            }
        }
    }
    
    
    if(disruptTimer <= 0){
        if(difficulty == 0){
            // EASY
            disruptTimer = 5;
            if(disruptions < 7){
                StartDisruption();
            }
        }
        else if(difficulty == 1){
            // MEDIUM
            disruptTimer = 2;
            if(disruptions < 3){
                StartDisruption();
            }
        }
        else if(difficulty == 2){
            // HARD
            disruptTimer = 3;
            int r = rand() % 3;
            if(r <= 1 && disruptions < 7){
                StartDisruption();
            }
        }
        else{
            // ENDLESS
            disruptTimer = 2;
            int r = rand() % 3;
            if(r <= 1 && disruptions < 7){
                StartDisruption();
            }
        }

        dis = true;
    }


    if(Input::KeyDown[KEY_0]){
        Scene::Load(0);
    }
}

void MainMini::StartDisruption(){
    disruptions += 1;
    attentionBar->GetScript<AttentionBar>()->numberOfDistrupters += 1;

    if(forwardPeopleOn.size() == 0){
        // Make someone walk on
        int r = rand() % forwardPeopleOff.size();
        entity->registry->entityTree[forwardPeopleOff[r]]->GetScript<PersonController>()->WalkOn();
        forwardPeopleOn.push_back(forwardPeopleOff[r]);
        forwardPeopleOff.erase(forwardPeopleOff.begin() + r);
    }

    // Pick someone in forwardPeopleOn to disrupt
    int r = rand() % forwardPeopleOn.size();
    // Start disruption (MAKE SURE they wait until they are done walking (just wait 2 seconds i guess?))
    int d = availableDisruptions.size() > 2 ? rand() % (availableDisruptions.size() - 2) : rand() % availableDisruptions.size();
    Transform& t = entity->registry->entityTree[forwardPeopleOn[r]]->GetComponent<TransformComponent>();
    float y = t.position.y - 20;
    // if size = 5 -> 8
    // otherwise -> 6
    float offset = 6;
    if(t.scale.x == 5.0){
        offset = 11;
    }
    else if(t.scale.x == 4.0){
        offset = 5.25;
    }
    float x = entity->registry->entityTree[forwardPeopleOn[r]]->GetScript<PersonController>()->goalX + offset;
    entity->registry->entityTree[availableDisruptions[d]]->GetScript<Disrupt>()->Appear(x, y, forwardPeopleOn[r], true);
    // Switch them to forwardPeopleDisrupt
    forwardPeopleDisrupt.push_back(forwardPeopleOn[r]);
    usedDisruptions[availableDisruptions[d]] = forwardPeopleOn[r];
    
    availableDisruptions.erase(availableDisruptions.begin() + d);
    forwardPeopleOn.erase(forwardPeopleOn.begin() + r);
}

void MainMini::FinishedDisruption(int disruptionId, int forwardId){
    availableDisruptions.push_back(disruptionId);
    forwardPeopleOn.push_back(forwardId);
    // Remove forwardId from forwardPeopleDisrupt
    forwardPeopleDisrupt.erase(std::remove(forwardPeopleDisrupt.begin(), forwardPeopleDisrupt.end(), forwardId), forwardPeopleDisrupt.end());
    usedDisruptions.erase(disruptionId);
    // set flag for forwardId to walk off after load back
    disrupter = forwardId;

    disruptions -= 1;
    attentionBar->GetScript<AttentionBar>()->numberOfSolves += 1;
    if(difficulty == 0 && attentionBar->GetScript<AttentionBar>()->numberOfSolves >= 3){
        difficulty = 1;
    }
    else if(difficulty == 1 && attentionBar->GetScript<AttentionBar>()->numberOfSolves >= 9){
        difficulty = 2;
    }
    else if(difficulty == 2 && attentionBar->GetScript<AttentionBar>()->numberOfSolves >= 15){
        difficulty = 3;
    }
}

void MainMini::ResetValues(){
    started = false;
    peopleOff.clear();
    peopleOn.clear();
    forwardPeopleOff.clear();
    forwardPeopleOn.clear();
    forwardPeopleDisrupt.clear();

    difficulty = 0;
    disruptions = 0;
    availableDisruptions.clear();
    usedDisruptions.clear();
    disrupter = 0;
}

bool MainMini::started = false;
std::vector<int> MainMini::peopleOff;
std::vector<int> MainMini::peopleOn;
std::vector<int> MainMini::forwardPeopleOff;
std::vector<int> MainMini::forwardPeopleOn;
std::vector<int> MainMini::forwardPeopleDisrupt;

int MainMini::difficulty = 0;
int MainMini::disruptions = 0;
std::vector<int> MainMini::availableDisruptions;
std::map<int, int> MainMini::usedDisruptions;
int MainMini::disrupter;

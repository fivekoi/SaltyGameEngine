#include "HowToControl.h"

// Called before the first frame of Update()
void HowToControl::Start(){
    for(int id : h2->childrenIds){
        entity->registry->entityTree[id]->GetComponent<TransformComponent>().position.y += 1000;
    }
    for(int id : h3->childrenIds){
        entity->registry->entityTree[id]->GetComponent<TransformComponent>().position.y += 1000;
    }
}

// Called every frame before Render()
void HowToControl::Update(float dt){
    if(Input::KeyDown[KEY_D]){
        if(pagenum == 0){
            for(int id : h1->childrenIds){
                entity->registry->entityTree[id]->GetComponent<TransformComponent>().position.y += 1000;
            }   
            for(int id : h2->childrenIds){
                entity->registry->entityTree[id]->GetComponent<TransformComponent>().position.y -= 1000;
            }   
        }
        else if(pagenum == 1){
            for(int id : h2->childrenIds){
                entity->registry->entityTree[id]->GetComponent<TransformComponent>().position.y += 1000;
            }   
            for(int id : h3->childrenIds){
                entity->registry->entityTree[id]->GetComponent<TransformComponent>().position.y -= 1000;
            }  
        }
        else{
            Scene::Load(0);
        }
        pagenum += 1;

        nav->text = "Press A/D to navigate ("+ std::to_string(pagenum + 1) + "/3)";
    }
    else if(Input::KeyDown[KEY_A]){
        if(pagenum == 1){
            for(int id : h1->childrenIds){
                entity->registry->entityTree[id]->GetComponent<TransformComponent>().position.y -= 1000;
            }   
            for(int id : h2->childrenIds){
                entity->registry->entityTree[id]->GetComponent<TransformComponent>().position.y += 1000;
            }   
            pagenum -= 1;

        }
        else if(pagenum == 2){
            for(int id : h2->childrenIds){
                entity->registry->entityTree[id]->GetComponent<TransformComponent>().position.y -= 1000;
            }   
            for(int id : h3->childrenIds){
                entity->registry->entityTree[id]->GetComponent<TransformComponent>().position.y += 1000;
            }  
            pagenum -= 1;

        }

        nav->text = "Press A/D to navigate ("+ std::to_string(pagenum + 1) + "/3)";
    }
}
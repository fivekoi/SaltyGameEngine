#include "Game/ECS/ECS.h"

#include <algorithm>
#include <deque>
#include <stack>

// #include #include "Game/Salty/SaltyDebug.h"
// TODO: this needs to be removed in actual game build, could be done with def
// needs to be availible in scripting anyways so need a way to remove it 
// maybe can #define something in Engine/.. and do #ifndef something
#include "Game/Components/TransformComponent.h"

// Static variable for component Ids
int IComponent::nextId = 0;

int Entity::GetId() const
{
    return id;
}

// Called whenever parentId is reassigned
void Entity::OnParentIdChanged(int prevParentId, int newParentId) {
    // Remove child from removeId
    if(prevParentId == -1){
        std::vector<int>& rChildren = registry->rootIds;
        rChildren.erase(std::remove(rChildren.begin(), rChildren.end(), id), rChildren.end()); // Erase-remove idiom
    }
    else{
        std::vector<int>& pChildren = registry->entityTree[prevParentId]->childrenIds;
        pChildren.erase(std::remove(pChildren.begin(), pChildren.end(), id), pChildren.end()); // Erase-remove idiom
    }

    // Reparent child to addId at targetPos
    if(newParentId == -1){
        registry->rootIds.push_back(id);
    }
    else{
        registry->entityTree[newParentId]->childrenIds.push_back(id);
    }
}

void Entity::Destroy()
{
    registry->DestroyEntity(*this);
}

void Entity::StartScripts(){
    for (const auto& pair : scripts) {
        pair.second->Start();
    }
}
void Entity::UpdateScripts(float deltaTime){
    for (const auto& pair : scripts) {
        pair.second->Update(deltaTime);
    }
}

Entity& Registry::CreateEntity(int parentId) // default = -1
{
    int entityId;

    if(freeIds.empty())
    { 
        // No free ids, expand entity ids
        entityId = numEntities++;
        // Registry Invariant: entityComponentSignatures.size() = entityTree.size();
        if(entityId >= entityComponentSignatures.size())
        {
            entityComponentSignatures.resize(entityId + 1);
            entityTree.resize(entityId + 1);
        }
    }
    else
    {
        // Free id availible
        entityId = freeIds.front();
        freeIds.pop_front();
    }

    entityTree[entityId] = std::make_unique<Entity>(entityId);
    // All entities have a transform
    Entity& entity = *entityTree[entityId].get();
    entity.registry = this;
    entity.AddComponent<TransformComponent>();
    entitiesToBeAdded.insert(entity); // Will be added to systems in Update()

    // Add as child to parentId
    bool validParent = -1 < parentId && parentId < entityTree.size() && entityTree[parentId];
    // if(parentId != -1 && !validParent) Debug::Log("Assigned Entity to invalid parent, defaulting to root", -1);
    // Add to root if an invalid parent is entered
    if(parentId == -1 || !validParent) rootIds.push_back(entityId);
    else {
        entity.parentId.ManuallySet(parentId);
        entityTree[parentId]->childrenIds.push_back(entityId);
    }

    return entity;
}
// NOTE: CreateEntity(int entityId) is only called by Engine, entityId = -1 -> place in arbitrary location
Entity& Registry::EngineCreateEntity(int entityId) // default = -1 // TODO: could potentially define out in game build
{
    int id = entityId;
    if(id == -1){ // Place at first open location
        if(freeIds.empty())
        { 
            // No free ids, expand entity ids
            id = numEntities++;
            // Registry Invariant: entityComponentSignatures.size() = entityTree.size();
            if(id >= entityComponentSignatures.size())
            {
                entityComponentSignatures.resize(id + 1);
                entityTree.resize(id + 1);
            }
        }
        else
        {
            // Free id availible
            id = freeIds.front();
            freeIds.pop_front();
        }
    }
    else{ // Place at specific entityId
        // We will keep freeIds as a deque despite having to iterate through it here 
        // Choosing to prioritize game efficiency over engine efficiency
        auto it = std::find(freeIds.begin(), freeIds.end(), entityId);
        
        // Should only be called by EntityExists edit currently, only occuring if we are re-adding a deleted entity
        assert(it != freeIds.end()); 
        
        freeIds.erase(it);
    }
    
    // assert(entityTree[entityId] == nullptr); // TODO: make sure this assertion is correct (might be a common break)
    entityTree[id] = std::make_unique<Entity>(id);
    // All entities have a transform
    Entity& entity = *entityTree[id].get();
    entity.registry = this;
    entity.AddComponent<TransformComponent>();
    entitiesToBeAdded.insert(entity); // TODO: i am not a fan of this still

    return entity;
}

void Registry::DestroyEntity(Entity entity)
{
    // TODO: should probably be a queue, doesnt really matter but feels right for some reason
    std::stack<int> removeStack;
    removeStack.push(entity.GetId());

    // Destroy entity and all of it's children
    while(!removeStack.empty()){
        int id = removeStack.top();
        removeStack.pop();

        for(int childId : entityTree[id]->childrenIds)
        {  removeStack.push(childId); }

        entitiesToBeRemoved.insert(id);
    }
}
void Registry::DestroyEntity(int entityId)
{
    std::stack<int> removeStack;
    removeStack.push(entityId);

    // Destroy entity and all of it's children
    while(!removeStack.empty()){
        int id = removeStack.top();
        removeStack.pop();

        for(int childId : entityTree[id]->childrenIds)
        {  removeStack.push(childId); }

        entitiesToBeRemoved.insert(id);
    }
}

void Registry::AddEntityToSystems(Entity entity)
{
    for(auto& system : systems)
    {
        if(system.second->CheckEntity(entity))
        { system.second->AddEntityToSystem(entity); }
    }
}

void Registry::RemoveEntityFromSystems(Entity entity, bool dontCheck)
{
    for(auto system : systems)
    {
        system.second->RemoveEntityFromSystem(entity, dontCheck);
    }
}

// Adds/Removes entities from systems TODO: i kinda wanna rename this for clarity
void Registry::Update()
{
    // Potentially remove entities from systems
    for(auto entity : entitiesToRecheck)
    {
        // dontCheck = false. We just want to remove entities that no longer belong to each system
        RemoveEntityFromSystems(entity, false);
    }
    entitiesToRecheck.clear();

    // Add entites from entitiesToBeAdded to registry
    for(auto entity : entitiesToBeAdded)
    { 
        AddEntityToSystems(entity);
    }
    entitiesToBeAdded.clear();

    // Remove entities from entitiesToBeRemoved to registry
    for(int entityId : entitiesToBeRemoved)
    {
        // Remove from parent's children
        if(entityTree[entityId]->parentId != -1){
            // Parent may have already been removed
            if(entityTree[entityTree[entityId]->parentId]){
                std::vector<int>& parentCs = entityTree[entityTree[entityId]->parentId]->childrenIds;
                parentCs.erase(std::remove(parentCs.begin(), parentCs.end(), entityId), parentCs.end()); // Erase-remove idiom
            }
        }
        else{
            rootIds.erase(std::remove(rootIds.begin(), rootIds.end(), entityId), rootIds.end()); // Erase-remove idiom
        }

        // dontCheck = true. Entity is being deleted, so needs to be removed regardless of components
        RemoveEntityFromSystems(*entityTree[entityId].get(), true);

        entityComponentSignatures[entityId].reset();

        // TODO: could have check to make sure id isnt already in list
        // should never happen but best to be sure
        freeIds.push_back(entityId);

        // Remove from entityTree
        // NOTE: this has to preserve the empty space, i.e. entityTree cannot be shrunk mid scene 
        entityTree[entityId] = nullptr; 
    }
    entitiesToBeRemoved.clear();
}

// Should only be called internally, resets all registry variables
void Registry::Reset() {
    entityTree.clear();
    rootIds.clear();

    numEntities = 0;
    componentPools.clear();
    entityComponentSignatures.clear();
    systems.clear();
    entitiesToBeAdded.clear();
    entitiesToBeRemoved.clear();
    freeIds.clear();
}
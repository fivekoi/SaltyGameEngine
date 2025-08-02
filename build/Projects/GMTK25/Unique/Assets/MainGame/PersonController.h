#pragma once
#include "SaltyEngine.h"

class PersonController : public IScript {
private:
    // Idle Anim
    std::vector<string> idleFrames;

    std::vector<string> walkFrames = {"Time\\16x32 Walk Cycle1.png", "Time\\16x32 Walk Cycle2.png", "Time\\16x32 Walk Cycle3.png", "Time\\16x32 Walk Cycle4.png"};
    bool walkingOn = false;
    float walkOnTimer = 0;
    bool walkingOff = false;

    int localFrame = 0;

    bool isIdle = true;;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    PersonController(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;

    // Will be set by MainMini
    float goalX;
    float startX;
    float facing;
    // Time update for animations
    void Tick(int frame);
    // Start walking on to stage
    void WalkOn();
    // Walk off of stage
    void WalkOff();
    // If they are idle (i.e. not walking)
    bool IsIdle();
};
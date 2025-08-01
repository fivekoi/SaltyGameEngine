#pragma once
#include "SaltyEngine.h"

class MainMini : public IScript {
private:
    std::vector<int> peopleOff;
    std::vector<int> peopleOn;

    int frameNum = 0;
    float timer = 0;

    float walkTimer = 0;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    MainMini(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};
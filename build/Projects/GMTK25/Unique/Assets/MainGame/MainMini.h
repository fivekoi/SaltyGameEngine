#pragma once
#include "SaltyEngine.h"

class MainMini : public IScript {
private:
    static std::vector<int> peopleOff;
    static std::vector<int> peopleOn;
    // For people facing forwards (who will disrupt)
    static std::vector<int> forwardPeopleOff;
    static std::vector<int> forwardPeopleOn;

    int frameNum = 0;
    float timer = 0;

    float walkTimer = 0;

    static bool started;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    MainMini(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};
#pragma once
#include "SaltyEngine.h"

class MainMini : public IScript {
private:
    static std::vector<int> peopleOff;
    static std::vector<int> peopleOn;
    // For people facing forwards (who will disrupt)
    static std::vector<int> forwardPeopleOff;
    static std::vector<int> forwardPeopleOn;
    static std::vector<int> forwardPeopleDisrupt;

    int frameNum = 0;
    float timer = 0;

    float walkTimer = 0;

    static bool started;

    // For disruptions
    // Easy: only one at a time (first 3)
    // Medium: up to 2 at a time (next 7)
    // Hard: up to 7 at a time (forever)
    static int difficulty;
    float disruptTimer = 5;
    static int disruptions;
    static std::vector<int> availableDisruptions;

    SF_ Entity* disruptionParent;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    MainMini(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;

    void StartDisruption();
    void FinishedDisruption(int disruptionId, int forwardId);
};
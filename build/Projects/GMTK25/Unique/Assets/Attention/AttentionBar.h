#pragma once
#include "SaltyEngine.h"

class AttentionBar : public IScript {
private:
    SF_ Text* scoreTxt;
    static int score;

    // If this reaches 0, then lose
    static float hype;

    SF_ int inMini;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    AttentionBar(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;

    void DDRInput(bool correct);

    static int numberOfDistrupters;
    static int numberOfSolves;
};
#pragma once
#include "SaltyEngine.h"

#include "../MainMini.h"

class Disrupt : public IScript {
private:
    float timer = 2;
    glm::vec2 where;

    // 0 = not on screen
    // 1 = waiting
    // 2 = disrupting
    int phase = 0;

    SF_ string key;
    int keyCode;
    int keyScene;

    SF_ Entity* mainMini;
    float fId;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    Disrupt(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;

    void Appear(float x, float y, int forwardId, bool wait);
};
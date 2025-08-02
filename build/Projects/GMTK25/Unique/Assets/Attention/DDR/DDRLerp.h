#pragma once
#include "SaltyEngine.h"

class DDRLerp : public IScript {
private:
    float start;
    float target;

    bool lerping = false;
    float timer;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    DDRLerp(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;

    void LerpTo(float x);
    void CancelLerp();
};
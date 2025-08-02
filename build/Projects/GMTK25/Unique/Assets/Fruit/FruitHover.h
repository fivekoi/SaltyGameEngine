#pragma once
#include "SaltyEngine.h"

class FruitHover : public IScript {
private:
    float centerY;
    bool up;

    float timer = 0;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    FruitHover(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};
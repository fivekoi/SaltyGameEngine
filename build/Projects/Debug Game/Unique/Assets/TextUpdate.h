#pragma once
#include "SaltyEngine.h"

class TextUpdate : public IScript {
private:
    SF_ Text* text;
    float timer = 0.0f;

    int counter = 0;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    TextUpdate(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};
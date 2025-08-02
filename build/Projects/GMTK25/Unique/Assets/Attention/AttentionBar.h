#pragma once
#include "SaltyEngine.h"

class AttentionBar : public IScript {
private:

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    AttentionBar(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;

    void DDRInput(bool correct);
};
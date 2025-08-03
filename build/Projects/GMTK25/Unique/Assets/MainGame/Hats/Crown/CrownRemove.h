#pragma once
#include "SaltyEngine.h"

class CrownRemove : public IScript {
private:
    SF_ Transform* text1;
    SF_ Transform* text2;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    CrownRemove(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};
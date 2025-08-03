#pragma once
#include "SaltyEngine.h"

class HowToControl : public IScript {
private:
    SF_ Entity* h1;
    SF_ Entity* h2;
    SF_ Entity* h3;

    int pagenum = 0;

    SF_ Text* nav;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    HowToControl(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};
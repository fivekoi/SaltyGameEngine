#pragma once
#include "SaltyEngine.h"

class DDR : public IScript {
private:
    SF_ Entity* w1;
    SF_ Entity* w2;
    SF_ Entity* w3;
    SF_ Entity* w4;

    SF_ Entity* a1;
    SF_ Entity* a2;
    SF_ Entity* a3;
    SF_ Entity* a4;

    SF_ Entity* d1;
    SF_ Entity* d2;
    SF_ Entity* d3;
    SF_ Entity* d4;

    std::vector<Entity*> availKeys;
    std::vector<int> availInputs = {KEY_W, KEY_W, KEY_W, KEY_W, KEY_A, KEY_A, KEY_A, KEY_A, KEY_D, KEY_D, KEY_D, KEY_D};

    
    std::vector<Entity*> usedKeys;
    std::vector<int> usedInputs;

    SF_ Entity* attention;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    DDR(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};
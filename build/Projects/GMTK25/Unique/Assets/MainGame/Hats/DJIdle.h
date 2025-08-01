#pragma once
#include "SaltyEngine.h"

class DJIdle : public IScript {
private:
    SF_ string idle1;
    SF_ string idle2;
    SF_ string idle3;
    SF_ string idle4;
    std::vector<string> idles;

    int i = 0;

    SF_ Sprite* sprite;
    float timer = 0;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    DJIdle(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};
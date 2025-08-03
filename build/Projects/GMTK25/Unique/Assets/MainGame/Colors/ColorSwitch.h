#pragma once
#include "SaltyEngine.h"

class ColorSwitch : public IScript {
private:
    SF_ Sprite* sprite;

    SF_ string green1;
    SF_ string green2;
    SF_ string orange1;
    SF_ string orange2;
    SF_ string red1;
    SF_ string red2;
    
    SF_ Entity* mini;

    string color1;
    string color2;

    float changeTimer = 1.5;
    bool toggle = false;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    ColorSwitch(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};
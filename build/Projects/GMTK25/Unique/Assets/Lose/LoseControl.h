#pragma once
#include "SaltyEngine.h"

class LoseControl : public IScript {
private:
    SF_ Text* scoreText;
    SF_ Entity* score;
    SF_ Transform* highScoreTransform;
    
public:
    // Initialization will be handled by engine (including that of SF_ variables)
    LoseControl(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};
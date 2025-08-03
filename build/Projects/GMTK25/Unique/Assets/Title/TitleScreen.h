#pragma once
#include "SaltyEngine.h"

class TitleScreen : public IScript {
private:
    SF_ Text* scoreTxt;

    static bool playMusic;

public:
    // Initialization will be handled by engine (including that of SF_ variables)
    TitleScreen(Entity* entity, Transform* transform, std::vector<SaltyType>& serializedVars);

    void Start() override;
    void Update(float dt) override;
};